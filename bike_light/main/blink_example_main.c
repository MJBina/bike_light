/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "led_ctrl.h"


static const char *TAG = "blink_example_main";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting app_main");

    /* Configure the peripheral according to the LED type */
    led_configure();

    while (1) {
        //  led_blink();
        //  led_cycle();
        led_bounce(12);
        // vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}
