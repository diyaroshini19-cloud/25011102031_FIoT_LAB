#!/usr/bin/env python3
"""Check the exact 28 task folders and required evaluation artifacts."""

from __future__ import annotations

import argparse
from pathlib import Path
import re
import sys
import xml.etree.ElementTree as ET


ROOT = Path(__file__).resolve().parents[2]
TASKS_8051 = [
    "8051/CAT2/TASK2B", "8051/CAT3/TASK3A", "8051/CAT4/TASK4A",
    "8051/CAT5/TASK5A", "8051/CAT5/TASK5B/TASK5B.1",
    "8051/CAT5/TASK5B/TASK5B.2", "8051/CAT5/TASK5B/TASK5B.3",
    "8051/CAT5/TASK5C", "8051/CAT6/TASK6A", "8051/CAT6/TASK6B",
    "8051/CAT7/TASK7A", "8051/CAT7/TASK7B", "8051/CAT7/TASK7C",
]
TASKS_STM32 = [
    "STM32/CAT8/TASK8A", "STM32/CAT8/TASK8B", "STM32/CAT8/TASK8C",
    "STM32/CAT9/TASK9A", "STM32/CAT9/TASK9B",
    "STM32/CAT10/TASK10A", "STM32/CAT10/TASK10B", "STM32/CAT10/TASK10C",
    "STM32/CAT11/TASK11A", "STM32/CAT11/TASK11B",
    "STM32/CAT12/TASK12A", "STM32/CAT12/TASK12B", "STM32/CAT12/TASK12C",
    "STM32/CAT13/TASK13", "STM32/CAT14/TASK14",
]


def checks_for(task: str) -> list[tuple[str, bool]]:
    base = ROOT / task
    if task.startswith("8051/"):
        files = [
            ("Keil project (*.uvproj or *.uvprojx)", any(base.glob("*.uvproj")) or any(base.glob("*.uvprojx"))),
            ("C source (*.c)", any(base.glob("*.c"))),
            ("STARTUP.A51", any(p.name.lower() == "startup.a51" for p in base.iterdir()) if base.is_dir() else False),
            ("Objects/ directory", (base / "Objects").is_dir()),
            ("Objects/*.hex", any((base / "Objects").glob("*.hex"))),
            ("README.md", (base / "README.md").is_file()),
        ]
    else:
        files = [
            ("*.ioc", any(base.glob("*.ioc"))),
            (".mxproject", (base / ".mxproject").is_file()),
            ("Core/ directory", (base / "Core").is_dir()),
            ("Drivers/ directory", (base / "Drivers").is_dir()),
            ("MDK-ARM/ directory", (base / "MDK-ARM").is_dir()),
            ("MDK-ARM/*.uvprojx", any((base / "MDK-ARM").glob("*.uvprojx"))),
            ("MDK-ARM/startup_*.s", any((base / "MDK-ARM").glob("startup_*.s"))),
            ("README.md", (base / "README.md").is_file()),
        ]
    return files


def expected_artifact(task: str, check: str) -> str:
    """Return the path or pattern behind a structural check."""
    base = Path(task)
    patterns = {
        "Keil project (*.uvproj or *.uvprojx)": f"{base}/*.uvproj or *.uvprojx",
        "C source (*.c)": f"{base}/*.c",
        "STARTUP.A51": f"{base}/STARTUP.A51",
        "Objects/ directory": f"{base}/Objects/",
        "Objects/*.hex": f"{base}/Objects/*.hex",
        "*.ioc": f"{base}/*.ioc",
        ".mxproject": f"{base}/.mxproject",
        "Core/ directory": f"{base}/Core/",
        "Drivers/ directory": f"{base}/Drivers/",
        "MDK-ARM/ directory": f"{base}/MDK-ARM/",
        "MDK-ARM/*.uvprojx": f"{base}/MDK-ARM/*.uvprojx",
        "MDK-ARM/startup_*.s": f"{base}/MDK-ARM/startup_*.s",
        "README.md": f"{base}/README.md",
    }
    return patterns.get(check, f"{base}/{check}")


def suspicious(root: Path) -> list[str]:
    found: list[str] = []
    markers = re.compile(r"\b(TODO|TBD|PLACEHOLDER|FILL\s+ME|NOT\s+IMPLEMENTED)\b", re.I)
    task_roots = [ROOT / task for task in TASKS_8051 + TASKS_STM32]
    for task_root in task_roots:
      for path in task_root.rglob("*"):
        if not path.is_file() or "Drivers" in path.parts:
          continue
        try:
            if path.stat().st_size == 0:
                found.append(f"{path.relative_to(ROOT)}: empty file")
                continue
            if path.suffix.lower() not in {".c", ".h", ".a51", ".s", ".md", ".ioc", ".uvproj", ".uvprojx", ".mxproject"}:
                continue
            data = path.read_text(errors="ignore")
            # Restrict marker matching to user-controlled text, not vendor source
            # trees, whose upstream comments legitimately contain TODO notes.
            if markers.search(data):
                found.append(f"{path.relative_to(ROOT)}: placeholder marker")
        except OSError:
            found.append(f"{path.relative_to(ROOT)}: unreadable")
    return found


def engineering_checks() -> list[tuple[str, bool, str]]:
    """Check project XML syntax and explicit source-file references.

    These checks are reported separately from the fixed 198 structural checks.
    """
    results: list[tuple[str, bool, str]] = []
    for task in TASKS_8051 + TASKS_STM32:
        base = ROOT / task
        for project in sorted((*base.glob("*.uvproj"), *base.glob("*.uvprojx"),
                               *(base / "MDK-ARM").glob("*.uvprojx"))):
            label = str(project.relative_to(ROOT))
            try:
                tree = ET.parse(project)
                results.append((label + " XML", True, "parsed"))
            except (ET.ParseError, OSError) as exc:
                results.append((label + " XML", False, str(exc)))
                continue
            missing = []
            for node in tree.findall(".//FilePath"):
                raw = (node.text or "").strip().strip('"').replace("\\", "/")
                if not raw or "$" in raw:
                    continue
                resolved = (project.parent / raw).resolve()
                if not resolved.exists():
                    missing.append(raw)
            results.append((label + " source references", not missing,
                            "all explicit file paths exist" if not missing else "missing: " + ", ".join(missing)))
    return results


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--quiet", action="store_true", help="print only the summary")
    args = parser.parse_args()
    tasks = [(x, "8051") for x in TASKS_8051] + [(x, "STM32") for x in TASKS_STM32]
    passed_tasks = passed_checks = failed_checks = 0
    for task, platform in tasks:
        checks = checks_for(task)
        task_ok = all(ok for _, ok in checks)
        passed_tasks += int(task_ok)
        passed_checks += sum(ok for _, ok in checks)
        failed_checks += sum(not ok for _, ok in checks)
        if not args.quiet:
            print(f"{ 'PASS' if task_ok else 'FAIL' } TASK {task}")
            for name, ok in checks:
                print(f"  { 'PASS' if ok else 'FAIL' } {name}")
                if not ok:
                    print(f"    MISSING: {expected_artifact(task, name)}")
    placeholders = suspicious(ROOT)
    total_tasks = len(tasks)
    total_checks = passed_checks + failed_checks
    structural_ok = passed_tasks == total_tasks and failed_checks == 0 and not placeholders
    print("\nSuspicious or empty files:")
    if placeholders:
        for item in placeholders:
            print(f"  FLAG {item}")
    else:
        print("  None found")
    print(f"\nTasks discovered: {total_tasks}")
    print(f"Tasks passed: {passed_tasks}")
    print(f"Tasks failed: {total_tasks - passed_tasks}")
    print(f"File checks passed: {passed_checks}/{total_checks}")
    print(f"File checks failed: {failed_checks}/{total_checks}")
    print(f"Structural status: {'PASS' if structural_ok else 'FAIL'}")
    print("\nEngineering configuration checks (separate from structural score):")
    checks = engineering_checks()
    for label, ok, detail in checks:
        if not args.quiet:
            print(f"  {'PASS' if ok else 'FAIL'} {label}: {detail}")
    print(f"Project XML/reference checks passed: {sum(ok for _, ok, _ in checks)}/{len(checks)}")
    overall = structural_ok and all(ok for _, ok, _ in checks)
    print(f"Overall status: {'PASS' if overall else 'FAIL'}")
    print("Compilation and physical hardware results are reported in PROJECT_DOCUMENTATION/Reports/ENGINEERING_VALIDATION_REPORT.md.")
    print("CAT10, CAT11 and CAT14 are included in the corrected mapping and structural checks.")
    return 0 if overall else 1


if __name__ == "__main__":
    sys.exit(main())
