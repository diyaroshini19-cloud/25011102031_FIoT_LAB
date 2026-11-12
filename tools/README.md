# STM32 GCC build support

`build_stm32_gcc.py` builds only the newly implemented GPIO tasks:

```sh
python3 build_stm32_gcc.py
python3 build_stm32_gcc.py STM32/CAT12/TASK12C
```

Requires Homebrew's `arm-none-eabi-gcc` and `arm-none-eabi-objcopy`. The script consumes the source list in each task's Keil project XML, compiles with `-ffreestanding`, uses ST's vendor GCC startup assembly, links with the supplied flash/RAM layouts, and writes `.elf`, `.hex`, objects and map files under that task's `Build-GCC/` directory. The minimal runtime only supplies `memset` and an empty `__libc_init_array`; these lab applications do not use libc or C++ constructors. It does not build or access CAT10/CAT14.

The Keil `.uvprojx` remains the IDE project. GCC output is a separate build product. Physical board validation is still required.
