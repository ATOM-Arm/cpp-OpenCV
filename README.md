# cpp-OpenCV: C++ and OpenCV Setup (MinGW/GCC + CMake)

This repository contains C++ example code using the OpenCV library for computer vision tasks.

This guide details the steps to develop computer vision applications in C++ with OpenCV on Windows using the MinGW (GCC) compiler and CMake, managed from VS Code.

# Documentation

OpenCV getting started [guide](https://docs.opencv.org/4.x/d2/de6/tutorial_py_setup_in_windows.html)

OpenCV [official documentation](https://docs.opencv.org/)

OpenCV [C++ tutorials](https://docs.opencv.org/4.x/d9/df8/tutorial_root.html)

OpenCV C++ [API reference](https://docs.opencv.org/4.x/d1/da0/group__core.html)


# 🚀 Installation and Configuration

## Prerequisites (Windows)

1. **MinGW (GCC):** Install a MinGW distribution (e.g., TDM-GCC or MinGW-w64) and ensure its `bin` directories are on the system `Path`.
2. **CMake:** Download and Install CMake at [this link](https://cmake.org/download) and choose the option to add it to the system `Path`.
3. **VS Code:** Install VS Code and the extensions: **C/C++** and **CMake Tools**.

## 1. Build and Install OpenCV (MinGW-compatible)

To avoid linkage errors, build OpenCV from source using MinGW.

1. **Download the Source:** Download OpenCV source (e.g., 4.x) from the [official site](https://opencv.org/releases) and extract to a location (example: `C:\opt\opencv-4.12.0`).

2. **Configure and Build (terminal):**
    Use CMake to generate MinGW Makefiles and then build and install:

    ```bash
    # Example configuration:
    cmake -S C:/opt/opencv-4.12.0 -B C:/opt/opencv_mingw_build -G "MinGW Makefiles" \
         -D CMAKE_BUILD_TYPE=Release \
         -D CMAKE_INSTALL_PREFIX="C:/opt/opencv_mingw" \
         -D BUILD_opencv_python3=OFF

    # Change to build directory
    cd C:/opt/opencv_mingw_build

    # Build and install (replace '12' with your CPU core count)
    mingw32-make -j12
    mingw32-make install
    ```

## 2. Configure PATH for OpenCV DLLs

Add the OpenCV DLL folder to your system PATH so executables can find runtime libraries:

1. Open Windows Environment Variables.

    Hit Win + R, type `sysdm.cpl`, go to the **Advanced** tab, and click **Environment Variables**.
2. Edit the user or system `Path`.
3. Add the DLL installation path (usually under `bin`), for example:
    ```
    C:\opt\opencv_mingw\x64\mingw\bin
    ```
    or in PowerShell:
    ```bash
    $env:PATH += ";C:\opt\opencv_mingw\x64\mingw\bin"
    ```
    to check the environment variable in the current session.
    ```bash
    echo $env:Path
    ```

Note: Close and reopen VS Code and terminals after updating PATH.

---

## 💻 Simple C++ Example with CMake

You can navigate to the [FirstTrip](FirstTrip/) folder for a simple example. Below are the steps to set up your own project.

### 1. CMakeLists.txt

Create this file at the project root. Set `OpenCV_DIR` to the folder containing `OpenCVConfig.cmake`.

```cmake
cmake_minimum_required(VERSION 3.0)
project(cpp_OpenCV)

# Path to the OpenCV installation created by MinGW
# This should point to the folder that contains 'OpenCVConfig.cmake'.
set(OpenCV_DIR "C:/opt/opencv_mingw/lib/cmake/opencv4" CACHE PATH "Path to OpenCV MinGW install")

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Create executable
add_executable(cpp_OpenCV main.cpp)

# Link OpenCV libraries (MinGW-compatible .a/.dll)
target_link_libraries(cpp_OpenCV ${OpenCV_LIBS})
```

Create `main.cpp` with the following code (or use the version from FirstTrip): [FirstTrip/main.cpp](FirstTrip/main.cpp)

Create `main.cpp` with the following code:

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

int main() {
    std::cout << "/* Starting */" << std::endl;
    cv::Mat image = cv::imread("blackhole.jpg");
    if (image.empty()) {
        std::cerr << "Error: Could not open image file." << std::endl;
        return -1;
    }

    // Create a window with fixed size (not resizable)
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(WINDOW_WIDTH, WINDOW_HEIGHT));

    cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
    cv::resizeWindow("Display Image", WINDOW_WIDTH, WINDOW_HEIGHT);

    cv::imshow("Display Image", resizedImage);
    cv::waitKey(0);
    return 0;
}
```

### 3. Configure the build with CMake

From your project directory:

```bash
mkdir build
cmake -B .\build\
```

Set the PATH for the current session (PowerShell):

```powershell
$env:PATH += ";C:\opt\opencv_mingw\x64\mingw\bin"
```

To persist for the current user (run in an elevated PowerShell or reopen the session afterwards):

```powershell
setx PATH "$($env:PATH);C:\opt\opencv_mingw\x64\mingw\bin"
```

After setting persistent PATH, close and reopen your terminal or IDE.

### 4. Build the project

Delete the existing build folder if it exists, then run the following commands to
```bash
Remove-Item -Recurse -Force build_debug, build_release;
```

Create debug and release build folders and build with MinGW Makefiles:

```bash
cmake -S . -B build_debug -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake -S . -B build_release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
```

Debug build:

```bash
# Build Debug
cmake --build build_debug

# Run the executable
.\build_debug\cpp_OpenCV.exe
```

Release build:

```bash
# Build Release
cmake --build build_release

# Run the executable
.\build_release\cpp_OpenCV.exe
```

