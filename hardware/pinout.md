# MicroPad V2 - Hardware Pinout Reference

## Core Specifications
* **MCU:** Microchip ATmega32U4 (8-bit AVR @ 16 MHz, 5V)
* **USB Interface:** Native Full-Speed USB 2.0 via Type-C
* **Status LED:** D1 (Active HIGH on Arduino Pin 8)
* **Power Circuit:** 5V Bus Powered with 500mA PTC Fuse

---

## Complete Pin Assignment Map

| Physical Control | Schematic Designator | ATmega32U4 Pin | Arduino Leonardo Pin | Default Function / Mapping |
| :--- | :--- | :--- | :--- | :--- |
| **Joystick X-Axis** | `U1 H1` | Pin 40 (`PF1`) | `A4` | Analog Input (0–1023) |
| **Joystick Y-Axis** | `U1 V1` | Pin 41 (`PF0`) | `A5` | Analog Input (0–1023) |
| **Joystick Click** | `U1 SEL+` | Pin 27 (`PD7`) | `D6` | Digital In (`INPUT_PULLUP`) / Left Click |
| **Potentiometer** | `RV1 Pin 2` | Pin 39 (`PF4`) | `A3` | Analog Input (0–1023) |
| **Tactile Button 1** | `SW1` | Pin 8 (`PB0`) | `D17` / `SS` | Digital In (`INPUT_PULLUP`) / `Ctrl + Z` |
| **Tactile Button 2** | `SW2` | Pin 9 (`PB1`) | `D15` / `SCK` | Digital In (`INPUT_PULLUP`) / `Ctrl + C` |
| **Tactile Button 3** | `SW3` | Pin 10 (`PB2`) | `D16` / `MOSI`| Digital In (`INPUT_PULLUP`) / `Ctrl + V` |
| **Tactile Button 4** | `SW4` | Pin 11 (`PB3`) | `D14` / `MISO`| Digital In (`INPUT_PULLUP`) / `Spacebar` |
| **Encoder 1 (Phase A)**| `SW6 Pin A` | Pin 18 (`PD0`) | `D3` *(INT0)* | Rotary Pulse (Hardware Interrupt) |
| **Encoder 1 (Phase B)**| `SW6 Pin B` | Pin 19 (`PD1`) | `D2` *(INT1)* | Rotary Direction (Volume Up/Down) |
| **Encoder 1 (Push)** | `SW6 S1` | Pin 20 (`PD2`) | `D0` / `RX` | Digital In (`INPUT_PULLUP`) / Mute |
| **Encoder 2 (Phase A)**| `SW7 Pin A` | Pin 21 (`PD3`) | `D1` / `TX` | Rotary Pulse |
| **Encoder 2 (Phase B)**| `SW7 Pin B` | Pin 25 (`PD4`) | `D4` | Rotary Direction (Scrub/Scroll) |
| **Encoder 2 (Push)** | `SW7 S1` | Pin 26 (`PD6`) | `D12` | Digital In (`INPUT_PULLUP`) / Enter |
| **Mode Switch (Pos 1)**| `SW8 Pin 1` | Pin 29 (`PB5`) | `D9` | Digital In (`INPUT_PULLUP`) |
| **Mode Switch (Pos 3)**| `SW8 Pin 4` | Pin 30 (`PB6`) | `D10` | Digital In (`INPUT_PULLUP`) |
| **Status LED** | `D1 Anode` | Pin 28 (`PB4`) | `D8` | Digital Out (Active HIGH) |
