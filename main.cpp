#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include <string.h>
#include <cstdlib>

#include "libraries/pico_display_2/pico_display_2.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "rgbled.hpp"
#include "button.hpp"

using namespace pimoroni;

ST7789 st7789(320, 240, ROTATE_0, false, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

RGBLED led(PicoDisplay2::LED_R, PicoDisplay2::LED_G, PicoDisplay2::LED_B);

Button button_a(PicoDisplay2::A);
Button button_b(PicoDisplay2::B);
Button button_x(PicoDisplay2::X);
Button button_y(PicoDisplay2::Y);

int main() {
    stdio_init_all();

    st7789.set_backlight(255);

    const uint LED_PIN = 2;
    const uint BUZZ_PIN = 9;
    const uint IN_PIN = 22;


    Pen WHITE = graphics.create_pen(255, 255, 255);


    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUZZ_PIN);
    gpio_set_dir(BUZZ_PIN, GPIO_OUT);

    gpio_init(IN_PIN);
    gpio_set_dir(IN_PIN, GPIO_IN);

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    uint in_val = 0;

    while (true) {
        led.set_rgb(0, 0, 0);

        RGB p = RGB::from_hsv(0.5, 1.0f, 0.5f);

        
        Pen BG = graphics.create_pen(p.r, p.g, p.b);
        Pen RED = graphics.create_pen(255,0, 0);



        if(button_a.raw()) {
            led.set_rgb(0, 0, 100);
        }

        
        if(button_b.raw()) {
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }

        if(button_x.raw()) {
            gpio_put(BUZZ_PIN, 1);
        } else {
            gpio_put(BUZZ_PIN, 0);
        }
        

        in_val = gpio_get(IN_PIN);

        if(in_val) {
            graphics.set_pen(RED);
        } else {
            graphics.set_pen(BG);
        }
        
        graphics.clear();
        
      

        graphics.set_pen(WHITE);
        graphics.text("Light",  Point(0, 50), 320); 
        graphics.text("Flash", Point(0, 175), 320);
        graphics.text("Buzz", Point(275, 50), 320);

        
        st7789.update(&graphics);
        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        //  gpio_put(LED_PIN, 1);
        // sleep_ms(1000);
        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        //  gpio_put(LED_PIN, 0);
        // sleep_ms(1000);
    }
}