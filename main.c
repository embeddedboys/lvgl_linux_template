#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "lvgl/lvgl.h"
#include "port/lv_port_disp.h"
#include "port/lv_port_indev.h"
#include "port/lv_port_tick.h"

#include "lvgl/demos/lv_demos.h"
#include "lvgl/examples/lv_examples.h"

/*******************
*       DEFINE
********************/
static void app_init(void);
static void app_exit(void);

static lv_group_t *g;


static void intr_sig_handler(int signal)
{
    app_exit();
}

static void app_init(void)
{
#if CROSS_COMPILE
    system("echo 0 > /sys/class/graphics/fbcon/cursor_blink");
#endif
    signal(SIGINT, intr_sig_handler);
}

static void app_exit(void)
{
    printf("app exiting ...");
#if CROSS_COMPILE
    system("echo 1 > /sys/class/graphics/fbcon/cursor_blink");
#endif
    printf(" done\n");
    exit(EXIT_SUCCESS);
}

static void hal_init(void)
{
    lv_init();

    lv_port_disp_init();
    lv_port_indev_init();
    lv_port_tick_init();

    g = lv_group_get_default();
    if (g == NULL) {
        g = lv_group_create();
        lv_group_set_default(g);
    }
}

int main(int argc, char **argv)
{
    app_init();
    hal_init();

    // ifconfig usb0 192.168.200.100
    // ping 192.168.200.101
    // mount -t nfs -o nolock,vers=3 192.168.200.101:/home/developer/nfs_share /mnt
    // cd /mnt && ./demo

    /* App here */
    printf("Launching App ...\n");
    // lv_demos_create(NULL, 0);
    // lv_demo_widgets();
    // lv_demo_benchmark();
    lv_demo_stress();
    // lv_demo_music();
    // lv_demo_flex_layout();
    // lv_demo_multilang();
    // lv_demo_transform();
    // lv_demo_scroll();
    // lv_demo_vector_graphic();

    // lv_example_file_explorer_1();

    for(;;) {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}
