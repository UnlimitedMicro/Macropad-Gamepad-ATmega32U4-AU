# MicroPad - Hardware Pinout & Circuit Map
# Copyright (C) 2026 UnlimitedMicro/ MicroPad Project
# This firmware is licensed under CC BY-NC-SA 4.0.
# Commercial use, reproduction, or sales are strictly prohibited.
## System Specifications
* **MCU:** Microchip ATmega32U4 (8-bit AVR @ 16 MHz, 5V)
* **USB Interface:** USB Type-C Receptacle with USBLC6-2SC6 ESD protection (`U3`)
* **Power:** 5V Bus-Powered via 500mA PTC Resettable Fuse (`F1`)
* **Status LED:** `D1` (Active HIGH on Arduino Pin 8 via 1k resistor `R6`)
* **Reset Circuit:** `SW5` Tactile Switch to GND with 10k pull-up (`R1`)
* **Programming Interface:** `J2` (6-Pin ISP Header for bootloader flashing)

---

## Complete Hardware Pinout Mapping

| Component | Schematic Ref | MCU Pin | Arduino Pin | Circuit Type | Default Action / Behavior |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Joystick X-Axis** | `U1 H1` | Pin 40 (`PF1`) | `A4` | Analog In | Cursor Horizontal Movement |
| **Joystick Y-Axis** | `U1 V1` | Pin 41 (`PF0`) | `A5` | Analog In | Cursor Vertical Movement |
| **Joystick Click** | `U1 SEL+` | Pin 27 (`PD7`) | `D6` | Digital In (`PULLUP`) | Mouse Left Click |
| **Slide Potentiometer** | `RV1 Pin 2`| Pin 39 (`PF4`) | `A3` | Analog In | Dynamic Zoom (`Ctrl + Scroll`) |
| **Mechanical Key 1** | `SW1` | Pin 8 (`PB0`) | `D17` / `SS` | Digital In (`PULLUP`) | Macro 1 (Mode Dependent) |
| **Mechanical Key 2** | `SW2` | Pin 9 (`PB1`) | `D15` / `SCK` | Digital In (`PULLUP`) | Macro 2 (Mode Dependent) |
| **Mechanical Key 3** | `SW3` | Pin 10 (`PB2`) | `D16` / `MOSI`| Digital In (`PULLUP`) | Macro 3 (Mode Dependent) |
| **Mechanical Key 4** | `SW4` | Pin 11 (`PB3`) | `D14` / `MISO`| Digital In (`PULLUP`) | Macro 4 (Mode Dependent) |
| **Encoder 1 (A)** | `SW6 Pin A` | Pin 18 (`PD0`) | `D3` *(INT0)* | Digital In (`PULLUP`) | Volume Knob (Pulse A) |
| **Encoder 1 (B)** | `SW6 Pin B` | Pin 19 (`PD1`) | `D2` *(INT1)* | Digital In (`PULLUP`) | Volume Knob (Pulse B) |
| **Encoder 1 (Click)** | `SW6 S1` | Pin 20 (`PD2`) | `D0` / `RX` | Digital In (`PULLUP`) | Mute / Unmute Toggle |
| **Encoder 2 (A)** | `SW7 Pin A` | Pin 21 (`PD3`) | `D1` / `TX` | Digital In (`PULLUP`) | Timeline Scrub / Scroll (Pulse A) |
| **Encoder 2 (B)** | `SW7 Pin B` | Pin 25 (`PD4`) | `D4` | Digital In (`PULLUP`) | Timeline Scrub / Scroll (Pulse B) |
| **Encoder 2 (Click)** | `SW7 S1` | Pin 26 (`PD6`) | `D12` | Digital In (`PULLUP`) | Return / Enter Key |
| **Mode Switch (Left)** | `SW8 Pin 1` | Pin 29 (`PB5`) | `D9` | Digital In (`PULLUP`) | **Game Mode** Active |
| **Mode Switch (Center)**| `SW8 Center`| *Floating* | *None* | Internal Pullups | **Mac Mode** Active |
| **Mode Switch (Right)**| `SW8 Pin 4` | Pin 30 (`PB6`) | `D10` | Digital In (`PULLUP`) | **Windows Mode** Active |
| **Status LED** | `D1 Anode` | Pin 28 (`PB4`) | `D8` | Digital Out | Board Power / Active Status |

---

## 6-Pin ISP Header (`J2`) Pinout

```text
       [Pin 1: MISO]  ●  ●  [Pin 2: +5V]
        [Pin 3: SCK]  ●  ●  [Pin 4: MOSI]
      [Pin 5: RESET]  ●  ●  [Pin 6: GND]
