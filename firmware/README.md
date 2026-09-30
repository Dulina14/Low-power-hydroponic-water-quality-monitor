# Firmware

The supplied `Hydroponic_System.zip` contains an academic project presentation, three flowchart JPEGs and editor settings, **not** ESP-IDF source files. The original, working `.c` / `.h` firmware sources were therefore not available to import.

An ESP32-C3 prototype previously demonstrated UART flashing/serial output, GPIO output, and DS18B20 temperature readings. Example-only reconstructed code was prepared in the curated download package; it is **not** the fully integrated and tested firmware.

The intended final ESP-IDF project should implement the sensor driver/HAL, ADC calibration, CRC-checked 1-Wire, float-switch GPIO wake and debounce, GPIO5-controlled sensor power, buzzer GPIO6, battery monitoring, FreeRTOS alarm/sensor/telemetry tasks, Wi-Fi communication with retries/timeouts, and coordinated timer + float-triggered deep sleep.

Firmware upload and verification remain outstanding.
