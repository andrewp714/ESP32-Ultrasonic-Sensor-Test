#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define TRIG_PIN GPIO_NUM_5
#define ECHO_PIN GPIO_NUM_18
#define SPEED_OF_SOUND 0.0343 // cm/us (speed of sound in air at 20°C)
#define TIMEOUT_US 30000      // 30ms timeout (covers max range of ~400 cm)

void hc_sr04_init(void) {
    // Configure TRIG pin as output
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << TRIG_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    // Configure ECHO pin as input
    io_conf.pin_bit_mask = (1ULL << ECHO_PIN);
    io_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&io_conf);
}

float measure_distance(void) {
    // Send 10us trigger pulse
    gpio_set_level(TRIG_PIN, 0);
    esp_rom_delay_us(2); // Precise 2us delay
    gpio_set_level(TRIG_PIN, 1);
    esp_rom_delay_us(10); // Precise 10us pulse
    gpio_set_level(TRIG_PIN, 0);

    // Wait for echo start (high)
    int64_t start_time = esp_timer_get_time();
    while (gpio_get_level(ECHO_PIN) == 0) {
        if (esp_timer_get_time() - start_time > TIMEOUT_US) {
            return -1.0; // Return -1 for out-of-range or no echo
        }
    }

    // Measure echo pulse duration
    start_time = esp_timer_get_time();
    while (gpio_get_level(ECHO_PIN) == 1) {
        if (esp_timer_get_time() - start_time > TIMEOUT_US) {
            return -1.0; // Timeout during echo high
        }
    }
    int64_t end_time = esp_timer_get_time();

    // Calculate distance
    float time_us = (float)(end_time - start_time);
    float distance = (time_us * SPEED_OF_SOUND) / 2.0;

    // Check if distance is within HC-SR04 range (2 cm to 400 cm)
    if (distance < 2.0 || distance > 400.0) {
        return -1.0;
    }

    return distance;
}

void app_main(void) {
    hc_sr04_init();
    while (1) {
        float distance = measure_distance();
        if (distance < 0) {
            printf("Distance: Out of range\n");
        } else {
            printf("Distance: %.2f cm\n", distance);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS); // Measure every 500ms
    }
}