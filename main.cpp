#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {

    const uint LED_PIN = 7;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
         gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
         gpio_put(LED_PIN, 0);
        sleep_ms(1000);
    }
}