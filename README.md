# Blom
Blom is a subset of [YDF(Yggdrasil Decision Forests)](https://github.com/google/yggdrasil-decision-forests) that runs the following algorithms:

1. CART
2. Decision Tree
3. Random Forest

Specifically, Blom aims to be a library that can easily, out-of-the box, be cross-compiled for ARM and Android.

## Getting started

## Linux

There are various ways to get started with Blom: 

1. on the command-line with vim(or its variants).

2. using an IDE such as Visual studio code(with CMake plugins) or JetBrains CLion.

3. using Docker with the enclosed dockerfile. Ideal if you don't want to install the prequisites on the host and have some knowledge of Docker.

#### Prequisites:

If you opt to use docker, you can safely skip installing the prequisites and go to step 4.

1. CMake

2. Ninja

3. Build-essentials i.e c++, make e.tc

#### Steps:

1. Configure the project

```
    cmake --preset=linux.x64-debug -S .
```

2. Build the project

```
    cmake --build --preset=linux.x64-debug
```

3. Run example executable;

```
cd builds/linux.x86_64/example
./example
```

4. Docker only steps:

   a. Build the image

        docker build -t blom .

   b. Run the image

        docker run -v $(pwd):/home/workspace/blom -u $(id -u):$(id -g) -it blom /bin/bash

   c. Build the project

        cmake --preset=linux.x64-debug -S . && cmake --build --preset=linux.x64-debug

## Windows

I would recommend using Visual studio.

##### Prequisites:

1. [Visual Studio 22](https://visualstudio.microsoft.com/downloads/) community or pro.

2. Visual studio "Desktop Development with c++" workload installed. This is available as part of the installer.
   The workload will enable support for CMake projects.

##### Steps:

1. Start Visual studio and select "Open a local folder".

2. Select folder where you have cloned the project.

3. Wait for Visual studio to download project dependencies and build.

4. On folder view change, select "CMake target view" to select targets. Search for "example" executable and set as default.

For more information refer to [Visual Studio documentation on CMake](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170).

##### Troubleshooting:

1. **Not all project dependencies were downloaded:**

   Go to project menu and "Delete cache and Reconfigure".
   
2. **If issues still persist:**
   
   (re)configure and build the project manually by going to "view menu", opening a terminal and running the following commands.

   a. Check your terminal prompt has the project directory set as the default directory.

   b. Check cmake is installed;

        cmake --version

   c. Configure the project;

        cmake --preset=windows.x64-debug -S .

   d. Build example;

        cmake --build --preset=windows.x64-debug --target example

   e. Or build all;

        cmake --build --preset=windows.x64-debug

## Cross-compiling

You can cross-compile the Blom for ARM or Android; however only the Android configurations are provided.

#### Prequisites:

1. [Android NDK](https://developer.android.com/ndk) OR

2. ARM GCC cross-compiler

3. To cross compile for ARM you will also need to create a `CMakeUserPreset.json` and a toolchain file.
   [CMake documentation](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html) is an excellent resource.

#### Steps for Android:

1. Add to the environment the variable `CMAKE_ANDROID_NDK` pointing to the root directory of Android NDK.
 
    Without this environment variable CMake will not enable the Android presets.

2. Phase 1: build all, in this case on a linux host.

        cmake --preset=linux.x64-debug -S . && cmake --build --preset=linux.x64-debug

   If on windows replace `linux` with `windows`.

   This step is necessary in order to generate the required protocol buffer C++ source files.

3. Phase 2: build for Android

        cmake --preset=android.v8a-debug -S . && cmake --build --preset=android.v8a-debug

For more options, review projects preset file.

