#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "port/lv_port_indev.h"

#include "lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.h"
#include "lvgl/demos/stress/lv_demo_stress.h"

/*******************
*       DEFINE
********************/
static void app_init(void);
static void app_exit(void);

#define MY_DISP_HOR_RES 128
static lv_group_t * g;

static pthread_mutex_t g_lvgl_tick_mutex = PTHREAD_MUTEX_INITIALIZER;

static void intr_sig_handler(int signal)
{
    app_exit();
}

static void app_init(void)
{
    system("echo 0 > /sys/class/graphics/fbcon/cursor_blink");

    signal(SIGINT, intr_sig_handler);
}

static void app_exit(void)
{
    printf("app exiting ...");

    system("echo 1 > /sys/class/graphics/fbcon/cursor_blink");

    printf(" done\n");
    exit(EXIT_SUCCESS);
}

static void hal_init(void)
{
    app_init();

    lv_init();
    fbdev_init();

    static lv_disp_draw_buf_t disp_buf;

    static lv_color_t buf_1[MY_DISP_HOR_RES * MY_DISP_HOR_RES];
    static lv_color_t buf_2[MY_DISP_HOR_RES * MY_DISP_HOR_RES];

    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, MY_DISP_HOR_RES * MY_DISP_HOR_RES);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_HOR_RES;
    disp_drv.full_refresh = 1;

    lv_disp_t *disp;
    disp = lv_disp_drv_register(&disp_drv);
    (void)disp;

    lv_port_indev_init();

    g = lv_group_get_default();
    if(g == NULL) {
        g = lv_group_create();
        lv_group_set_default(g);
    }

    lv_indev_t * cur_drv = NULL;
    for(;;) {
        cur_drv = lv_indev_get_next(cur_drv);
        if(!cur_drv) {
            break;
        }

        if(cur_drv->driver->type == LV_INDEV_TYPE_KEYPAD) {
            lv_indev_set_group(cur_drv, g);
        }

        if(cur_drv->driver->type == LV_INDEV_TYPE_ENCODER) {
            lv_indev_set_group(cur_drv, g);
        }
    }
}

static void *tick_thread(void *data)
{
    for(;;) {
        pthread_mutex_lock(&g_lvgl_tick_mutex);
        lv_task_handler();
        usleep( 5000 );
        lv_tick_inc( 5000 );
        pthread_mutex_unlock(&g_lvgl_tick_mutex);
    }

    return NULL;
}

int main( int argc, char **argv )
{
    pthread_t tid;

    hal_init();

    printf("Creating sys_tick ...\n");
    pthread_create(&tid, NULL, tick_thread, NULL);

    // ifconfig usb0 192.168.200.100
    // ping 192.168.200.101
    // mount -t nfs -o nolock,vers=3 192.168.200.101:/home/developer/nfs_share /mnt

    /* App here */
    printf( "Launching App ...\n" );
    // lv_demo_benchmark();
    // lv_demo_keypad_encoder();
    lv_demo_stress();
    // lv_demo_widgets();
    // lv_example_checkbox_1();

    while (1);

    return 0;
}
