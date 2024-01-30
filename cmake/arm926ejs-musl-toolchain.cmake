#SET(CROSS_COMPILE 1)
#set(CMAKE_SYSTEM_NAME Linux)

set(TOOLCHAIN_PATH /opt/arm-buildroot-linux-musleabi_sdk-buildroot)
set(TOOLCHAIN_SYSROOT ${TOOLCHAIN_PATH}/arm-buildroot-linux-musleabi/sysroot/)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/arm-buildroot-linux-musleabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/arm-buildroot-linux-musleabi-g++)

include_directories(${TOOLCHAIN_SYSROOT}/usr/include/drm)