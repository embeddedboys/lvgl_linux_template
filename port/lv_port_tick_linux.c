#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include "../lvgl/lvgl.h"

#include "lv_port_tick.h"

#if 0
static pthread_t tid;
static pthread_mutex_t g_lvgl_tick_mutex = PTHREAD_MUTEX_INITIALIZER;


static void *tick_thread(void *data)
{
    for (;;) {
        pthread_mutex_lock(&g_lvgl_tick_mutex);
        usleep(5000);
        lv_tick_inc(5);
        pthread_mutex_unlock(&g_lvgl_tick_mutex);
    }

    return NULL;
}

void lv_port_tick_init()
{
    printf("Creating sys_tick ...\n");
    pthread_create(&tid, NULL, tick_thread, NULL);
}
#endif

void lv_port_tick_init()
{
    /* do nothing, keep compatible */
}

uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
