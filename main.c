#include <stdio.h>

#include "pico/stdlib.h"

#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#else
#include "hardware/gpio.h"
#endif

extern void threadx_main(void);

int main() {
    stdio_init_all();

    #ifdef CYW43_WL_GPIO_LED_PIN
    if (cyw43_arch_init()) {
        return -1;
    }
    #else
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    #endif

    threadx_main();
    return 0;
}
