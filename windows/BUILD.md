# GNG for Windows

## Common Requirements

- **SDL2**
- **SDL2_image**
- **SDL2_ttf**

The following must be in the libs directory:

- **SDL2.dll**
- **SDL2_image.dll**
- **SDL2_ttf.dll**
- **libwinpthread-1.dll**
- **libstdc++-6.dll**
- **libgcc_s_seh-1.dll**

## Requirements on Windows

- **clang or GCC**

## Building on Windows

To build GNG on Windows, first create a bin folder for the binary to be built into. Then run `make` (if you're using GCC run `make CC=g++`).

## Requirements on Linux

- **quasi-msys2**

## Building on Linux

To build GNG on Linux, first create a bin folder for the binary to be built into. Then enter the `quasi-msys2` shell and run `make CC=win-clang++`.
