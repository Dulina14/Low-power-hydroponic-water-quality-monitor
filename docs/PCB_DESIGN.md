# PCB design details

The final target is **ESP32-C3-MINI-1-H4X**, not ESP8684. The uploaded Altium project contains `Embedded_Project.PrjPcb`, a PCB document, four schematic sheets, a BOM, and an output job. The files are currently in a separate curated archive pending binary upload.

## Power system

3 × AA batteries feed a TPS63001 3.3 V buck–boost converter. The power nets are `VBAT_RAW`, `SYSTEM_3V3`, `SENSOR_3V3`, and GND. A P-channel MOSFET switches sensor power so the TDS board and DS18B20 do not draw supply current during deep sleep. A 4.7 kΩ DS18B20 data pull-up must use `SENSOR_3V3`, not the always-on supply. Check all I/O pin states for back-powering.

## Connections

| Signal | ESP32-C3 GPIO | Interface |
| --- | ---: | --- |
| Battery divider | GPIO0 | ADC1 |
| PP float switch | GPIO3 | Filter / Schmitt, deep-sleep-capable |
| TDS analog output | GPIO4 | ADC1, input conditioning |
| Sensor-power MOSFET | GPIO5 | P-channel high-side |
| Buzzer MOSFET | GPIO6 | N-channel low-side; gate pulldown |
| DS18B20 data | GPIO10 | 1-Wire, pull-up to switched supply |
| Native USB D− | GPIO18 | USB-C ESD interface |
| Native USB D+ | GPIO19 | USB-C ESD interface |
| UART RX | GPIO20 | Optional UART programming/debug |
| UART TX | GPIO21 | Optional UART programming/debug |

Strapping GPIO2, GPIO8 and GPIO9 require appropriate reset/boot bias. GPIO9 is used for BOOT. The module antenna requires the official keep-out pattern and board-edge placement.

## Power and interfaces

The source design has USB-C for programming/data, a native-USB ESD device and CC pull-down resistors. The uploaded schematic should be reviewed to determine if USB-C powers the board or whether AA cells are required during flashing; USB 5 V must never be wired directly across alkaline cells.

External connector interfaces are intended for the TDS module, waterproof DS18B20, passive float, buzzer and battery pack. The water-level wake network uses RC conditioning plus a Schmitt trigger to reject reed-bounce and water sloshing. Firmware should additionally debounce and avoid immediate repeated wake when the float holds the active wake level.

## Design-rule status

The archive's September 27, 2026 PCB design-rule report recorded **zero unrouted nets** and **five violations** where 0.2 mm drilled vias failed the configured 0.3 mm minimum. This is an unresolved configuration/design issue. Do not label this a fabrication-approved PCB. Re-run checks in Altium after finalizing footprint pad counts (particularly the imported ESP32-C3 module), antenna clearances and JLCPCB's actual process limits.

This documentation describes the provided design snapshot; it does not certify electrical function or JLCPCB part availability.
