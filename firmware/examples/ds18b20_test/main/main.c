/* Reconstructed development-board proof of concept.
 * Prototype GPIO6; final PCB GPIO10. External 4.7 kOhm DATA pull-up required.
 * IMPORTANT: This demo does not check DS18B20 scratchpad CRC and
 * uses software 1-Wire timing. Harden it before production use.
 */
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"
#define DS18B20_GPIO GPIO_NUM_6
static void drive_low(void) {
    gpio_set_level(DS18B20_GPIO, 0);
    gpio_set_direction(DS18B20_GPIO, GPIO_MODE_OUTPUT);
}
static void release_line(void) {
    gpio_set_direction(DS18B20_GPIO, GPIO_MODE_INPUT);
}
static int reset_bus(void) {
    drive_low(); esp_rom_delay_us(480);
    release_line(); esp_rom_delay_us(70);
    int present = !gpio_get_level(DS18B20_GPIO);
    esp_rom_delay_us(410);
    return present;
}
static void write_bit(int bit) {
    drive_low();
    if (bit) { esp_rom_delay_us(6); release_line(); esp_rom_delay_us(64); }
    else { esp_rom_delay_us(60); release_line(); esp_rom_delay_us(10); }
}
static int read_bit(void) {
    drive_low(); esp_rom_delay_us(6); release_line(); esp_rom_delay_us(9);
    int bit = gpio_get_level(DS18B20_GPIO);
    esp_rom_delay_us(55);
    return bit;
}
static void write_byte(uint8_t val) {
    for (int i=0; i<8; ++i) { write_bit(val & 1); val >>= 1; }
}
static uint8_t read_byte(void) {
    uint8_t val=0;
    for (int i=0; i<8; ++i) { if (read_bit()) val |= (1 << i); }
    return val;
}
static int start_conversion(void) {
    if (!reset_bus()) return 0;
    write_byte(0xCC);
    write_byte(0x44);
    return 1;
}
static int read_temperature(float *out) {
    if (!reset_bus()) return 0;
    write_byte(0xCC);
    write_byte(0xBE);
    uint8_t low=read_byte(), high=read_byte();
    int16_t raw=(int16_t)((uint16_t)low | ((uint16_t)high << 8));
    *out=raw/16.0f;
    return 1;
}
void app_main(void) {
    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << DS18B20_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&cfg));
    printf("DS18B20 temperature test started\n");
    while (1) {
        if (!start_conversion()) {
            printf("DS18B20 not detected\n");
        } else {
            vTaskDelay(pdMS_TO_TICKS(750));
            float t=0;
            if (read_temperature(&t)) printf("Temperature: %.2f C\n",t);
            else printf("Temperature read error\n");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
