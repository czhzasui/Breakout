cmake_minimum_required(VERSION 3.10)
project(Breakout)

set(CMAKE_CXX_STANDARD 11)

#source /opt/fsl-imx-fb/4.1.15-2.0.0/environment-setup-cortexa9hf-neon-poky-linux-gnueabi
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/arm-poky-linux-gnueabi-gcc.sh)
set(CMAKE_CXX_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/arm-poky-linux-gnueabi-g++.sh)
set(CMAKE_ASM_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/arm-poky-linux-gnueabi-gcc.sh)
set(CMAKE_AR arm-poky-linux-gnueabi-ar CACHE FILEPATH "Archiver")
set(CMAKE_C_FLAGS " -march=armv7-a -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a9  --sysroot=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi  -O2 -pipe -g -feliminate-unused-debug-types -fdebug-prefix-map=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi= " CACHE STRING "CFLAGS")
set(CMAKE_CXX_FLAGS " -march=armv7-a -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a9  --sysroot=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi  -O2 -pipe -g -feliminate-unused-debug-types -fdebug-prefix-map=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi=  -fvisibility-inlines-hidden" CACHE STRING "CXXFLAGS")
set(CMAKE_ASM_FLAGS " -march=armv7-a -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a9  --sysroot=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi  -O2 -pipe -g -feliminate-unused-debug-types -fdebug-prefix-map=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi= " CACHE STRING "ASM FLAGS")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional CFLAGS for release")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional CXXFLAGS for release")
set(CMAKE_ASM_FLAGS_RELEASE "-DNDEBUG" CACHE STRING "Additional ASM FLAGS for release")
set(CMAKE_C_LINK_FLAGS " -march=armv7-a -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a9  --sysroot=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi  -Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed" CACHE STRING "LDFLAGS")
set(CMAKE_CXX_LINK_FLAGS " -march=armv7-a -mfpu=neon  -mfloat-abi=hard -mcpu=cortex-a9  --sysroot=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi  -O2 -pipe -g -feliminate-unused-debug-types -fdebug-prefix-map=/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi=  -fvisibility-inlines-hidden -Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed" CACHE STRING "LDFLAGS")

set(CMAKE_FIND_ROOT_PATH /opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(ENV{QT_CONF_PATH} /opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/i686-pokysdk-linux/usr/bin/qt5/qt.conf)

set(CMAKE_INSTALL_RPATH)

list(APPEND CMAKE_MODULE_PATH "/opt/fsl-imx-fb/4.1.15-2.0.0/sysroots/cortexa9hf-neon-poky-linux-gnueabi/usr/share/cmake/Modules/")

set(CMAKE_LIBRARY_PATH /usr/lib /lib)

set(OE_QMAKE_PATH_EXTERNAL_HOST_BINS $ENV{OECORE_NATIVE_SYSROOT}/usr/bin/qt5)
set(CMAKE_PREFIX_PATH $ENV{OECORE_TARGET_SYSROOT}/usr)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS REQUIRED Core DBus Quick)

add_definitions(-DEGL_API_FB -DLINUX)

#common setting
include_directories(common)
include_directories(common/include)
include_directories(blizzard/lib)
include_directories(blizzard/src)

#cmake for breakout
aux_source_directory(blizzard/lib/stb_image BREAKOUT_SOURCE_FILES)
aux_source_directory(blizzard/src BREAKOUT_SOURCE_FILES)
aux_source_directory(common/ui BREAKOUT_SOURCE_FILES)
aux_source_directory(breakout BREAKOUT_SOURCE_FILES)

add_executable(breakout ${BREAKOUT_SOURCE_FILES})

target_link_libraries(breakout
        Qt5::Core
        Qt5::DBus
        -lEGL
        -lpthread
        -lGLESv2
        -lopencv_highgui
        -lopencv_calib3d
        -lopencv_features2d
        -lopencv_flann
        -lopencv_imgproc
        -lopencv_core
        -lopencv_imgcodecs)


