### Dependencies

- [cmake](https://cmake.org/download/):  3.9
- [Qt](https://www.qt.io/download-open-source):   5.9.1
- [OpenSSL](https://www.openssl.org/): Use the latest available 1.0 version (**NOT** 1.1) of OpenSSL to avoid security vulnerabilities.
- [VHACD](https://github.com/virneo/v-hacd)(clone this repository)(Optional)

### CMake External Project Dependencies

These dependencies need not be installed manually. They are automatically downloaded on the platforms where they are required.  
- [Bullet Physics Engine](https://github.com/bulletphysics/bullet3/releases):  2.83
- [GLEW](http://glew.sourceforge.net/):   1.13
- [glm](https://glm.g-truc.net/0.9.8/index.html):  0.9.8
- [Oculus SDK](https://developer.oculus.com/downloads/):   1.11 (Win32) / 0.5 (Mac)
- [OpenVR](https://github.com/ValveSoftware/openvr):   1.0.6 (Win32 only)
- [Polyvox](http://www.volumesoffun.com/):   0.2.1
- [QuaZip](https://sourceforge.net/projects/quazip/files/quazip/):   0.7.3
- [SDL2](https://www.libsdl.org/download-2.0.php):   2.0.3
- [Intel Threading Building Blocks](https://www.threadingbuildingblocks.org/):   4.3
- [Sixense](http://sixense.com/):   071615
- [zlib](http://www.zlib.net/):   1.28 (Win32 only)
- nVidia Texture Tools:   2.1

The above dependencies will be downloaded, built, linked and included automatically by CMake where we require them. The CMakeLists files that handle grabbing each of the following external dependencies can be found in the [cmake/externals folder](cmake/externals). The resulting downloads, source files and binaries will be placed in the `build/ext` folder in each of the subfolders for each external project.

These are not placed in your normal build tree when doing an out of source build so that they do not need to be re-downloaded and re-compiled every time the CMake build folder is cleared. Should you want to force a re-download and re-compile of a specific external, you can simply remove that directory from the appropriate subfolder in `build/ext`. Should you want to force a re-download and re-compile of all externals, just remove the `build/ext` folder.

If you would like to use a specific install of a dependency instead of the version that would be grabbed as a CMake ExternalProject, you can pass -DUSE_LOCAL_$NAME=0 (where $NAME is the name of the subfolder in [cmake/externals](cmake/externals)) when you run CMake to tell it not to get that dependency as an external project.

### OS Specific Build Guides

* [BUILD_OSX.md](BUILD_OSX.md) - additional instructions for OS X.
* [BUILD_LINUX.md](BUILD_LINUX.md) - additional instructions for Linux.
* [BUILD_WIN.md](BUILD_WIN.md) - additional instructions for Windows.
* [BUILD_ANDROID.md](BUILD_ANDROID.md) - additional instructions for Android

### CMake

Hifi uses CMake to generate build files and project files for your platform.

#### Qt

In order for CMake to find the Qt5 find modules, you will need to set a QT_CMAKE_PREFIX_PATH environment variable pointing to your Qt installation.

This can either be entered directly into your shell session before you build or in your shell profile (e.g.: ~/.bash_profile, ~/.bashrc, ~/.zshrc - this depends on your shell and environment).

The path it needs to be set to will depend on where and how Qt5 was installed. e.g.

    export QT_CMAKE_PREFIX_PATH=/usr/local/qt/5.6.2/clang_64/lib/cmake/
    export QT_CMAKE_PREFIX_PATH=/usr/local/Cellar/qt5/5.6.2/lib/cmake
    export QT_CMAKE_PREFIX_PATH=/usr/local/opt/qt5/lib/cmake

#### Generating build files

Create a build directory in the root of your checkout and then run the CMake build from there. This will keep the rest of the directory clean.

    mkdir build
    cd build
    cmake ..

If cmake gives you the same error message repeatedly after the build fails (e.g. you had a typo in the QT_CMAKE_PREFIX_PATH that you fixed but the `.cmake` files still cannot be found), try removing `CMakeCache.txt`.

#### Variables

Any variables that need to be set for CMake to find dependencies can be set as ENV variables in your shell profile, or passed directly to CMake with a `-D` flag appended to the `cmake ..` command.

For example, to pass the QT_CMAKE_PREFIX_PATH variable during build file generation:

    cmake .. -DQT_CMAKE_PREFIX_PATH=/usr/local/qt/5.6.2/lib/cmake

#### Finding Dependencies

The following applies for dependencies we do not grab via CMake ExternalProject (OpenSSL is an example), or for dependencies you have opted not to grab as a CMake ExternalProject (via -DUSE_LOCAL_$NAME=0). The list of dependencies we grab by default as external projects can be found in [the CMake External Project Dependencies section](#cmake-external-project-dependencies).

You can point our [Cmake find modules](cmake/modules/) to the correct version of dependencies by setting one of the three following variables to the location of the correct version of the dependency.

In the examples below the variable $NAME would be replaced by the name of the dependency in uppercase, and $name would be replaced by the name of the dependency in lowercase (ex: OPENSSL_ROOT_DIR, openssl).

* $NAME_ROOT_DIR - pass this variable to Cmake with the -DNAME_ROOT_DIR= flag when running Cmake to generate build files
* $NAME_ROOT_DIR - set this variable in your ENV
* HIFI_LIB_DIR - set this variable in your ENV to your High Fidelity lib folder, should contain a folder '$name'

### Optional Components

#### Devices

You can support external input/output devices such as Leap Motion, MIDI, and more by adding each individual SDK in the visible building path. Refer to the readme file available in each device folder in [interface/external/](interface/external) for the detailed explanation of the requirements to use the device.
