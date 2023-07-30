#include <stdio.h>
#include "tx_api.h"
#include "pico/stdlib.h"

#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#else
#include "hardware/gpio.h"
#endif

#define TX_STACK_SIZE 1024
#define TX_BYTE_POOL_0_SIZE 9120

UCHAR memory_area[TX_BYTE_POOL_0_SIZE];
TX_BYTE_POOL byte_pool_0;

/* ThreadX object control blocks */
TX_THREAD thread_0;

/* Thread prototypes */
void thread_0_entry(ULONG thread_input);

UCHAR g_led_state = 0;

/* Main entry point */
void threadx_main(void)
{
    tx_kernel_enter();
}

void tx_application_define(void *first_unused_memory)
{
    CHAR *pointer = TX_NULL;

    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", &memory_area[0], 
                                                         TX_BYTE_POOL_0_SIZE);

    /* Allocate stack for thread 0 */
    tx_byte_allocate(&byte_pool_0, (VOID **)&pointer, TX_STACK_SIZE, TX_NO_WAIT);
    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0, pointer, 
                                     TX_STACK_SIZE, 16, 16, 4, TX_AUTO_START);
}

void toggle_led(void)
{
    #ifdef CYW43_WL_GPIO_LED_PIN
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, g_led_state);
    #else
    gpio_put(PICO_DEFAULT_LED_PIN, g_led_state);
    #endif

    g_led_state ^= 1;
}

void thread_0_entry(ULONG thread_input)
{
    while (true)
    {
        toggle_led();
        tx_thread_sleep(500);
    }
}
