# Low-Power Hydroponic Water Quality Monitor

A 3×AA battery-powered water quality monitoring PCB designed in **Altium Designer 2026**, built around **ESP32-C3-MINI-1-H4X**. The design monitors approximate TDS, water temperature, water level, and battery voltage, with a MOSFET-switched sensor rail, buzzer, native USB-C programming, and planned laptop Wi-Fi telemetry.

> **Design-stage project.** The editable PCB design and real Gerber-derived front/back previews are in the [curated project archive prepared for upload](https://github.com/Dulina14/Low-power-hydroponic-water-quality-monitor/). Binary Altium files and images have **not yet been pushed to this repository**. Do not fabricate from unreviewed exports.

## PCB front and back

The real front and back 2D previews have been prepared from the Gerber layers in the uploaded PCB project. **Their upload to `images/pcb-front.png` and `images/pcb-back.png` is pending.** They are *Gerber previews*, not assembled-board photographs.

After those image files are uploaded, this section can display:

| Front | Back |
|:--:|:--:|
| [Front preview (upload pending)](images/pcb-front.png) | [Back preview (upload pending)](images/pcb-back.png) |

## System overview

| Module | Description |
|---|---|
| MCU | ESP32-C3-MINI-1-H4X, Wi-Fi, RTC deep sleep |
| Power | 3 × AA alkaline, TPS63001 3.3 V buck–boost |
| TDS | MD0838 board, ADC1 / GPIO4 |
| Water temperature | DS18B20, GPIO10, powered through `SENSOR_3V3` |
| Water level | Passive PP float reed switch, filtered / Schmitt GPIO3 wake |
| Battery | `VBAT_RAW` resistor-divider to ADC1 / GPIO0 |
| Warning | Active buzzer through N-channel MOSFET / GPIO6 |
| Programming | Native USB Serial/JTAG over USB-C (GPIO18/19) |

There are no LCD or LED indicators.

## Docs

- [Detailed PCB hardware notes](docs/PCB_DESIGN.md)
- [Firmware status and planned architecture](firmware/README.md)

## Verification status

An earlier ESP32-C3 development board successfully built/flashed, operated a GPIO output, and read the DS18B20 (~22.9–23.0 °C). The ZIP supplied for firmware contained **diagrams and a presentation PDF but no firmware `.c` / `.h` source**, so there is no basis to claim that the integrated Wi-Fi / FreeRTOS firmware is in this repository.

The supplied Altium PCB DRC from **2026-09-27** reported **five hole-size violations** (0.2 mm via drills against the configured 0.3 mm minimum), despite zero unrouted nets. A fresh DRC, ERC, pad/antenna review, and JLCPCB manufacturing review are still required.

The source Altium and exported Gerber files, a PDF of the four schematic sheets/BOM, selected component libraries, actual PCB preview images, and reconstructed *example-only* prototype firmware are packaged separately for selective import. Do not mistake them for verified final production release assets.
