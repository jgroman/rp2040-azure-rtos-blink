#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

extern void threadx_blink(void);

int main() {
    stdio_init_all();

    if (cyw43_arch_init()) {
        return -1;
    }

    threadx_blink();
    return 0;
}
