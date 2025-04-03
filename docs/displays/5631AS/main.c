#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "led_strip.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_random.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// 7 Digit display example
// https://github.com/ashus3868/3-digit-7-Segment-ESP-IDF/blob/main/main/3_digit_7_segment.c

// Sort pins alphabetically for easy of usage!
// 1 on, 0 off
const int seven_seg_pins[7] = {
    GPIO_NUM_20,    // PIN 11 (A)
    GPIO_NUM_10,   // PIN 7 (B)
    GPIO_NUM_2,    // PIN 4 (C)
    GPIO_NUM_1,    // PIN 2 (D)
    GPIO_NUM_0,    // PIN 1 (E)
    GPIO_NUM_19,   // PIN 10 (F)
    GPIO_NUM_3    // PIN 5 (G)
    // GPIO_NUM_22,   // PIN 3 (DP) - do not use dot for now
};

// Reversed: 1 off, 0 on
const int digit_select[3] = {
    GPIO_NUM_11,  // 8  (DIG 3)
    GPIO_NUM_18,  // 9  (DIG 2)
    GPIO_NUM_21,   // 12 (DIG 1)
};

// Sorted pins alphabetically for easy of usage!
// Check each digit activation BOOL
const int numbers[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},  // 0
    {0, 1, 1, 0, 0, 0, 0},  // 1
    {1, 1, 0, 1, 1, 0, 1},  // 2
    {1, 1, 1, 1, 0, 0, 1},  // 3
    {0, 1, 1, 0, 0, 1, 1},  // 4
    {1, 0, 1, 1, 0, 1, 1},  // 5
    {1, 0, 1, 1, 1, 1, 1},  // 6
    {1, 1, 1, 0, 0, 0, 0},  // 7
    {1, 1, 1, 1, 1, 1, 1},  // 8
    {1, 1, 1, 1, 0, 1, 1}   // 9
}; 

int count = 0;
char number[3] = "000";
                            
// Do not used
#define LED_STRIP_USE_DMA 0

// LED OPTS
#define TIME_TICK_MS 500

#define LED_STRIP_LED_COUNT 1
#define LED_STRIP_MEMORY_BLOCK_WORDS 0 // let the driver choose a proper memory block size automatically

#define LED_STRIP_GPIO_PIN 8
#define LED_STRIP_RMT_RES_HZ (10 * 1000 * 1000)

static const char *TAG = "blink";

led_strip_handle_t configure_led(void) {
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO_PIN, // The GPIO that connected to the LED strip's data line
        .max_leds = LED_STRIP_LED_COUNT,      // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812,        // LED strip model
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color order of the strip: GRB
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };

    // LED strip backend configuration: RMT
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
        .resolution_hz = LED_STRIP_RMT_RES_HZ, // RMT counter clock frequency
        .mem_block_symbols = LED_STRIP_MEMORY_BLOCK_WORDS, // the memory block size used by the RMT channel
        .flags = {
            .with_dma = LED_STRIP_USE_DMA,     // Using DMA can improve performance when driving more LEDs
        }
    };

    // LED Strip object handle
    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    ESP_LOGI(TAG, "Created LED strip object with RMT backend");
    return led_strip;
}

int random_int_range(int min, int max) {    
    // Return random int from the range.
    // Use to blink led with random values.
    return min + (esp_random() % (max - min + 1));
}

void led_control_pixel(int i, led_strip_handle_t led_strip) {
    // Simple colour
    int RED = random_int_range(1, 255);
    int GREEN = random_int_range(1, 255);
    int BLUE = random_int_range(1, 255);
    ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, i, RED, GREEN, BLUE));
}

void led_control_hsv(int i, led_strip_handle_t led_strip) {
    // Color with saturation and brightness
    int hue = random_int_range(1, 360);  // MAX 360
    int saturation = random_int_range(1, 255); // MAX 255
    int brightLvl = random_int_range(1, 2);  // MAX 255
    ESP_ERROR_CHECK(led_strip_set_pixel_hsv(led_strip, i, hue, saturation, brightLvl));
}

void beep_setup() {
    // Clean the PIN and setup usage
    gpio_reset_pin(GPIO_NUM_23);
    gpio_set_direction(GPIO_NUM_23, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_NUM_23, GPIO_PULLUP_ONLY);
    gpio_set_level(GPIO_NUM_23, 0);
}

void pin_beep(bool led_on_off) {
    // Bip - simple beeper
    if (led_on_off) {
        gpio_set_level(GPIO_NUM_23, 1); // Bip
    } else {
        gpio_set_level(GPIO_NUM_23, 0); // Not Bip
    }
}

void display_setup() {
    // Set all GPIO pins to required mode.
    // Draw 888 at start!
    for (int x = 0; x < 10; x++) {
        if (x >= 7) {
            // Always reset all GPIO used:
            gpio_reset_pin(digit_select[x - 7]);
            gpio_set_direction(digit_select[x - 7], GPIO_MODE_OUTPUT);
            gpio_set_pull_mode(digit_select[x - 7], GPIO_PULLUP_ONLY);
            // Activate digit 1-3 segment once:
            gpio_set_level(digit_select[x - 7], 0);
            // Will be set to normal during the loop use
        }
        else {
            // Always reset all GPIO used:
            gpio_reset_pin(seven_seg_pins[x]);
            gpio_set_direction(seven_seg_pins[x], GPIO_MODE_OUTPUT);
            gpio_set_pull_mode(seven_seg_pins[x], GPIO_PULLUP_ONLY);
            // Draw '8' for all integers
            gpio_set_level(seven_seg_pins[x], 1);
            // Will be set to normal during the loop use
        }
    }
    ESP_LOGI(TAG, "Display test will show '888' at the beggining of setup!");
    // Wait for 1 second
    vTaskDelay(pdMS_TO_TICKS(500));
}

void digit_display() {
    // Variants used:
    // Only activate one poisiton at time - does not work
    // DIG3, DIG2, DIG1
    // 0     1     1   - On (DIG3), Off (DIG2, DIG1)
    // 1     0     1   - On (DIG2), Off (DIG1, DIG3)
    // 1     1     0   - On (DIG1), Off (DIG2, DIG3)
    // Activate 1,2,3 poisitons simultaneously
    // 0     1     1   - On (DIG3)
    // 0     0     1   - On (DIG3, DIG2)
    // 0     0     0   - On (DIG3, DIG2, DIG1)
    // Reversed
    // 1     1     0   - On (DIG1), Off (DIG2, DIG3)
    // 1     0     0   - On (DIG1, DIG2), Off (DIG3)
    // All Off
    // 1     1     1   - Off (DIG3, DIG2, DIG1)
    for (int j = 0; j < 3; j++) {
        int c = number[j] - '0';
        if (j == 0) {
            gpio_set_level(digit_select[0], 0);
            gpio_set_level(digit_select[1], 1);
            gpio_set_level(digit_select[2], 1);
        }
        else if (j == 1) {
            gpio_set_level(digit_select[0], 0);
            gpio_set_level(digit_select[1], 0);
            gpio_set_level(digit_select[2], 1);
        }
        else if (j == 2) {
            gpio_set_level(digit_select[0], 0);
            gpio_set_level(digit_select[1], 0);
            gpio_set_level(digit_select[2], 0);
        }
        for (int i = 0; i < 7; i++) {
            gpio_set_level(seven_seg_pins[i], numbers[c][i]);
        }
        // vTaskDelay(pdMS_TO_TICKS(1));
        // vTaskDelay(1);
    }
}

void count_blinks_display(bool led_on_off) {
    // 7seg 3 digit display used to count blinks from 0 to 999 and reset
    if (led_on_off) {
        // Run only at True
        count += 1;
        ESP_LOGI(TAG, "Led toggled %d times!", count);
        if (count < 10) {
            number[0] = '0';
            number[1] = '0';
            number[2] = count + '0';
        }
        else if ((count >= 10) && (count <= 99)) {
            number[0] = '0';
            number[1] = (count / 10) + '0';
            number[2] = (count % 10) + '0';
        }
        else if ((count >= 100) && (count <= 999)) {
            number[0] = (count / 100) + '0';
            number[1] = ((count % 100) / 10) + '0';
            number[2] = (count % 10) + '0';
        }
        else {
            ESP_LOGI(TAG, "Number reset to 000 at %d", count);
            count = 0;
            number[0] = '0';
            number[1] = '0';
            number[2] = '0';
        }
        ESP_LOGI(TAG, "Draw number: %s ", number);
        // Count blinks draw display
        for (size_t i = 0; i < 12; i++)
        {
            digit_display();
        }
        // ESP_LOGI(TAG, "Display refreshed\n\n");
    }
}

void led_blink(bool led_on_off, led_strip_handle_t led_strip) {
    // Use to show board alive
    if (led_on_off) {
        /* Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color */
        for (int i = 0; i < LED_STRIP_LED_COUNT; i++) {
            led_control_hsv(i, led_strip);
        }
        /* Refresh the strip to send data */
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        // ESP_LOGI(TAG, "LED ON!");

        // count blinks
        count_blinks_display(led_on_off);
        // Beep pin
        pin_beep(led_on_off);

    } else {
        /* Set all LED off to clear all pixels */
        ESP_ERROR_CHECK(led_strip_clear(led_strip));
        // ESP_LOGI(TAG, "LED OFF!");
    }
}

void app_main(void)
{
    // Set display ping ans draw 888 for 1 second at the beggining.
    display_setup();
    // Setup BIP pin
    beep_setup();
    // Led setup
    led_strip_handle_t led_strip = configure_led();
    bool led_on_off = false;
    ESP_LOGI(TAG, "Start blinking LED and Beep");
    while (1) {
        // Led blink
        led_blink(led_on_off, led_strip);
        // Reset
        led_on_off = !led_on_off;
        // Sleep
        vTaskDelay(pdMS_TO_TICKS(TIME_TICK_MS));
    }
}