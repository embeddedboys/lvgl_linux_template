file(GLOB_RECURSE EXT_SOURCES
        "lv_drivers/sdl/*.c"
        "port/lv_port_sdl.c"
	"port/lv_port_tick_linux.c"
)

file(GLOB_RECURSE EXT_INCLUDES
        "lv_drivers/sdl/*.h"
)
