# cmake_template

中文 | [English](README.md)

这是一个只支持 Linux 的 CMake 工程模板，使用现代 CMake、CMakePresets.json、Ninja 和 VSCode CMake Tools 工作流。

更详细的模板说明、图形化构建步骤和第三方库配置请访问：

<http://tungchiahui.cn/zh-cn/wiki/2023-10-05-cplusplus-jiao-xue/ch21-cmake-gong-cheng-mu-ban>

## 依赖

Fedora:

```bash
sudo dnf install cmake ninja-build eigen3-devel gdb
```

Ubuntu/Debian:

```bash
sudo apt install cmake ninja-build libeigen3-dev gdb
```

## 构建

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

安装 CMake Tools 扩展后，它会自动识别 `CMakePresets.json`。如果要断点调试，再安装 Microsoft C/C++ 扩展和 GDB。

1. 选择 `linux-debug` 或 `linux-release` configure preset。
2. 点击 Configure。
3. 点击 Build。
4. 选择 `cmake_template` 作为运行/调试 target。
5. 点击 CMake Tools 的运行按钮或 Debug 按钮。

日常开发时，可以直接运行或调试 build 目录里的程序：

```bash
./build/linux-debug/src/cmake_template
```

只有在验证安装结果时，才需要 install 后运行：

```bash
cmake --install build/linux-debug
./install/linux-debug/bin/cmake_template
```

## 目录结构

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

`lib1` 和 `lib2` 都在自己模块内部查找并链接 Eigen。最终可执行文件名与项目名一致：`cmake_template`。
