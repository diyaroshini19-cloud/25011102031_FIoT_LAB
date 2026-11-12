#!/usr/bin/env python3
"""Build the eligible new STM32 GPIO tasks with ARM GCC and ST CMSIS startup."""

from __future__ import annotations

import argparse
from pathlib import Path
import subprocess
import sys
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[2]
SUPPORT = Path(__file__).resolve().parent / "tools"
TASKS = {
    "STM32/CAT8/TASK8B": ("cortex-m3", "STM32F103x6", "f1"),
    "STM32/CAT8/TASK8C": ("cortex-m3", "STM32F103x6", "f1"),
    "STM32/CAT12/TASK12A": ("cortex-m4", "STM32F401xE", "f4"),
    "STM32/CAT12/TASK12B": ("cortex-m4", "STM32F401xE", "f4"),
    "STM32/CAT12/TASK12C": ("cortex-m4", "STM32F401xE", "f4"),
}


def run(command: list[str]) -> None:
    subprocess.run(command, check=True)


def build(task: str, cpu: str, define: str, family: str) -> None:
    base = ROOT / task
    project = next((base / "MDK-ARM").glob("*.uvprojx"))
    tree = ET.parse(project)
    sources: list[Path] = []
    for node in tree.findall(".//FilePath"):
        raw = (node.text or "").strip().replace("\\", "/")
        if raw.endswith(".c"):
            source = (project.parent / raw).resolve()
            if not source.is_file():
                raise FileNotFoundError(f"Project source does not exist: {source}")
            if source not in sources:
                sources.append(source)

    driver = "STM32F1xx_HAL_Driver" if family == "f1" else "STM32F4xx_HAL_Driver"
    device = "STM32F1xx" if family == "f1" else "STM32F4xx"
    include_dirs = [
        base / "Core/Inc",
        base / f"Drivers/{driver}/Inc",
        base / f"Drivers/{driver}/Inc/Legacy",
        base / f"Drivers/CMSIS/Device/ST/{device}/Include",
        base / "Drivers/CMSIS/Include",
    ]
    output = base / "Build-GCC"
    output.mkdir(exist_ok=True)
    objects = []
    common = ["arm-none-eabi-gcc", f"-mcpu={cpu}", "-mthumb", "-std=gnu11",
              "-ffreestanding", "-ffunction-sections", "-fdata-sections",
              f"-D{define}", "-DUSE_HAL_DRIVER"]
    common += [f"-I{directory}" for directory in include_dirs]
    for index, source in enumerate(sources):
        obj = output / f"{source.stem}_{index}.o"
        run(common + ["-c", str(source), "-o", str(obj)])
        objects.append(obj)

    startup = (base / "Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103x6.s"
               if family == "f1" else
               base / "Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f401xe.s")
    startup_object = output / "startup.o"
    run(["arm-none-eabi-gcc", f"-mcpu={cpu}", "-mthumb", "-x", "assembler-with-cpp",
         f"-D{define}", str(startup), "-c", "-o", str(startup_object)])
    runtime_object = output / "stm32_gcc_runtime.o"
    run(["arm-none-eabi-gcc", f"-mcpu={cpu}", "-mthumb", "-ffreestanding", "-fno-builtin",
         "-c", str(SUPPORT / "stm32_gcc_runtime.c"), "-o", str(runtime_object)])

    elf = output / f"{base.name}.elf"
    linker = SUPPORT / ("stm32_f103c6.ld" if family == "f1" else "stm32f401re.ld")
    run(["arm-none-eabi-gcc", f"-mcpu={cpu}", "-mthumb", "-nostdlib",
         "-Wl,--gc-sections", f"-Wl,-Map={output / (base.name + '.map')}",
         f"-T{linker}", str(startup_object), *map(str, objects), str(runtime_object),
         "-lgcc", "-o", str(elf)])
    run(["arm-none-eabi-objcopy", "-O", "ihex", str(elf), str(elf.with_suffix(".hex"))])
    print(f"PASS {task}: {len(sources)} C sources, ELF and Intel HEX")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("tasks", nargs="*", help="default: build all supported tasks")
    args = parser.parse_args()
    selected = args.tasks or list(TASKS)
    unknown = sorted(set(selected) - set(TASKS))
    if unknown:
        parser.error("unknown task(s): " + ", ".join(unknown))
    try:
        for task in selected:
            cpu, define, family = TASKS[task]
            build(task, cpu, define, family)
    except (OSError, subprocess.CalledProcessError, ET.ParseError, StopIteration) as exc:
        print(f"BUILD FAILED: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
