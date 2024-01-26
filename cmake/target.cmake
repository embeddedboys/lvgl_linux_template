include(${PROJECT_SOURCE_DIR}/cmake/arm926ejs-musl-toolchain.cmake)

file(GLOB_RECURSE EXT_SOURCES
        "lv_drivers/indev/evdev.c"
        "port/lv_port_indev.c"
        #"lv_drivers/display/fbdev.c"
        #"port/lv_port_disp_fbdev.c"
        "lv_drivers/display/drm.c"
        "port/lv_port_disp_drm.c"
        "port/lv_port_tick_linux.c"
)

file(GLOB_RECURSE EXT_INCLUDES
        #"lv_drivers/display/fbdev.h"
        "lv_drivers/display/drm.h"
        "lv_drivers/indev/evdev.h"
)
