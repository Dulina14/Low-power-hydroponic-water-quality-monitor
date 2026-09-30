# System architecture

The embedded-system design targets fewer than ten FreeRTOS tasks, two wake initiators, sensor acquisition, low-power operation and Wi-Fi reporting.

### Main events

1. A timer wakes the ESP32-C3 periodically (nominal design interval: ~15 minutes).
2. A passive float reed switch triggers GPIO3 hardware wake to investigate low water.

After a deep-sleep event, the ESP restarts application initialization and checks the wake cause. A GPIO wake is not an ISR executing while the CPU remains asleep.

### Planned tasks

| Task | Priority | Responsibility |
| --- | ---: | --- |
| Alarm | 3 | Confirm float event, drive buzzer, enqueue warning |
| Sensor | 2 | Switch sensor power, sample TDS, read temperature and water state |
| Telemetry | 1 | Connect Wi-Fi with timeouts, transmit/acknowledge, disconnect |

DS18B20 conversion (up to 750 ms at 12-bit) is intended to overlap with 30 TDS ADC samples taken ~40 ms apart. A filtered TDS voltage is temperature-compensated and converted to an estimated ppm reading. The design does not measure pH or identify chemical nutrients.

For a float switch that remains active, re-entering level-triggered GPIO wake immediately would create a wake loop. Debounce and confirm alarm/recovery with independent delays, using temporary timer-only wake while the condition remains active.

**Status:** This is the described design intent. The three uploaded ZIPs did not contain complete ESP-IDF implementation sources.
