//
// Created by markj on 6/1/2024.
//

#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

#include "led_ctrl.h"

static const char *TAG = "led_ctrl";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

static uint8_t s_led_state = 0;

#ifdef CONFIG_BLINK_LED_STRIP

static led_strip_handle_t led_strip;

void led_blink(void)
{
    ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");

    /* If the addressable LED is enabled */
    if (s_led_state) {
        /* Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color */
        led_strip_set_pixel(led_strip, 0, 16, 16, 16);   //  White
        /* Refresh the strip to send data */
        led_strip_refresh(led_strip);
    } else {
        /* Set all LED off to clear all pixels */
        led_strip_clear(led_strip);
    }
    s_led_state = !s_led_state;
}

void led_cycle(void)
{
    /* If the addressable LED is enabled */
    switch (s_led_state)
    {
        default:
            s_led_state = 0;
        case 0: led_strip_clear(led_strip); break;  //  LED Off
        case 1: led_strip_set_pixel(led_strip, 0, 16, 0, 0); break; //  LED Red
        case 2: led_strip_set_pixel(led_strip, 0, 0, 16, 0); break; //  LED Blue
        case 3: led_strip_set_pixel(led_strip, 0, 0, 0, 16); break; //  LED Green
        case 4: led_strip_set_pixel(led_strip, 0, 16, 16, 16); break; //  All LED On
        case 5: led_strip_set_pixel(led_strip, 0, 255, 255, 255); break; //  All LED On
    }
    led_strip_refresh(led_strip);
    s_led_state++;
};

void led_bounce(int num_leds)
{
    static int led = 0;
    static bool up = true;

    // ESP_LOGI(TAG, "led bounce (%d)", led);

    led_strip_clear(led_strip);
    led_strip_set_pixel(led_strip, led, 64, 0, 0);
    led_strip_refresh(led_strip);
    if (up)
    {
        if (++led >= (num_leds-1)) {
            up = false;
        }
    }
    else
    {
        if (--led <= 0) {
            up = true;
        }
    }

}

void led_configure(void)
{
    ESP_LOGI(TAG, "Example configured to blink addressable LED!");
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = BLINK_GPIO,
        .max_leds = 12, // at least one LED on board
    };
#if CONFIG_BLINK_LED_STRIP_BACKEND_RMT
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
#elif CONFIG_BLINK_LED_STRIP_BACKEND_SPI
    led_strip_spi_config_t spi_config = {
        .spi_bus = SPI2_HOST,
        .flags.with_dma = true,
    };
    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
#else
#error "unsupported LED strip backend"
#endif
    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);
}

#elif CONFIG_BLINK_LED_GPIO

static void blink_led(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, s_led_state);
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

#else
#error "unsupported LED type"
#endif

