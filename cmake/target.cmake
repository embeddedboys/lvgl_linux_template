include(${PROJECT_SOURCE_DIR}/cmake/arm926ejs-musl-toolchain.cmake)

file(GLOB_RECURSE EXT_SOURCES
        #"port/lv_port_indev.c"
        # "port/lv_port_disp_fbdev.c"
        "port/lv_port_disp_drm.c"
        "port/lv_port_tick_linux.c"
)

file(GLOB_RECURSE EXT_INCLUDES

)
