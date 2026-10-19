# cmake_template

[中文](README-zh_CN.md) | English

A Linux-only CMake project template using modern CMake, CMake presets, Ninja, and the VSCode CMake Tools workflow.

For detailed documentation, graphical build instructions, and third-party dependency configuration, visit:

<http://tungchiahui.cn/en-us/wiki/2023-10-05-cplusplus-jiao-xue/ch21-cmake-gong-cheng-mu-ban>

## Requirements

Fedora:

```bash
sudo dnf install cmake ninja-build eigen3-devel gdb
```

Ubuntu/Debian:

```bash
sudo apt install cmake ninja-build libeigen3-dev gdb
```

## Build

Debug:

```bash
cmake --preset linux-debug
cmake --build --preset linux-debug
cmake --install build/linux-debug
./install/linux-debug/bin/cmake_template
```

Release:

```bash
cmake --preset linux-release
cmake --build --preset linux-release
cmake --install build/linux-release
./install/linux-release/bin/cmake_template
```

## VSCode

Install the CMake Tools extension. It automatically detects `CMakePresets.json`. For breakpoint debugging, also install the Microsoft C/C++ extension and GDB.

1. Select the `linux-debug` or `linux-release` configure preset.
2. Click Configure.
3. Click Build.
4. Select `cmake_template` as the run/debug target.
5. Click the CMake Tools Run or Debug button.

During development, run or debug the build-tree executable directly:

```bash
./build/linux-debug/src/cmake_template
```

Use install only when you want to verify the installed layout:

```bash
cmake --install build/linux-debug
./install/linux-debug/bin/cmake_template
```

## Layout

```text
.
├── CMakeLists.txt
├── CMakePresets.json
├── cmake/
│   └── ProjectOptions.cmake
└── src/
    ├── main.cpp
    ├── lib1/
    │   ├── CMakeLists.txt
    │   ├── inc/lib1/eigen3_test.hpp
    │   └── src/eigen3_test.cpp
    └── lib2/
        ├── CMakeLists.txt
        ├── inc/lib2/eigen3_test.hpp
        └── src/eigen3_test.cpp
```

`lib1` and `lib2` each find and link Eigen where they use it. The executable is named after the project: `cmake_template`.
