cmake_minimum_required(VERSION 3.10)
project(HamsterBearHelmet)

#set(CMAKE_C_STANDARD 11)
SET(CROSS_COMPILE 1)
set(CMAKE_SYSTEM_NAME Linux)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
include_directories(./)
file(GLOB_RECURSE INCLUDES "lvgl/*.h"  "./*.h"
                        "lv_drivers/display/fbdev.h"
                        "lv_drivers/indev/evdev.h"
                        )
file(GLOB_RECURSE SOURCES  "lvgl/src/*.c"
                        "port/lv_port_indev.c"
                        "lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.c"
                        "lvgl/demos/stress/lv_demo_stress.c"
                        "lvgl/demos/widgets/*.c"
                        "lvgl/demos/benchmark/*.c"
                        "lv_drivers/display/fbdev.c"
                        "lv_drivers/indev/evdev.c")

option(BUILD_FOR_TARGET "Compile this program for target system" ON)

#configure_file (
#	"${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
#	"${CMAKE_CURRENT_SOURCE_DIR}/config.h"
#)

message("set cross compile toochain")
set(CMAKE_C_COMPILER "/opt/arm-buildroot-linux-musleabi_sdk-buildroot/bin/arm-buildroot-linux-musleabi-gcc")


# here to include native or port file


set(CMAKE_BUILD_TYPE "Release")
set(WARINGS "-Wall -Wextra \
                                                -Wshadow -Wundef -Wmaybe-uninitialized -Wmissing-prototypes -Wno-discarded-qualifiers \
                                                -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized \
                                                -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default  \
                                          -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated  \
                                                -Wempty-body -Wshift-negative-value -Wstack-usage=2048 \
            -Wtype-limits -Wsizeof-pointer-memaccess -Wpointer-arith")
SET(CMAKE_C_FLAGS_RELEASE " -O3 ${WARINGS}")
SET(CMAKE_C_FLAGS_DEBUG "-static -O3 -g ${WARINGS}")

# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)

link_libraries(pthread)

add_executable(demo main.c ${SOURCES} ${INCLUDES} ${EXT_SOURCES} ${EXT_INCLUDES})