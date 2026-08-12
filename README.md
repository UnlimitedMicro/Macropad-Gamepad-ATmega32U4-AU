# MicroPad V2 - Dual Rotary & Analog USB Controller

MicroPad V2 is an open-source, programmable USB HID macro pad and gaming controller powered by the **ATmega32U4**. It provides native plug-and-play USB input across Windows, macOS, and Linux without requiring drivers.

---

## Hardware Highlights
* **Dual EC11 Rotary Encoders:** Dedicated hardware dials for volume, scrubbing, scrolling, or brush sizing with integrated push-click switches.
* **Analog Thumbstick:** Fluid 2-axis analog control with push-button click.
* **4 Programmable Macro Buttons:** Zero-latency shortcuts for editing timelines, macros, or gaming.
* **SP3T Mode Switch:** On-the-fly profile switching between macro, mouse, and gamepad modes.
* **Hardware Protection:** USB-C interface protected by a USBLC6 ESD clamp and a 500mA PTC resettable fuse.

---

## Setup & Flashing Guide

1. **Install Arduino IDE:** Download from [arduino.cc](https://www.arduino.cc/en/software).
2. **Install Required Libraries:**
   * Go to **Sketch $\rightarrow$ Include Library $\rightarrow$ Manage Libraries...**
   * Search for and install **`HID-Project`** by *NicoHood*.
   * Search for and install **`Encoder`** by *Paul Stoffregen*.
3. **Upload Firmware:**
   * Open `firmware/v2_controller/v2_controller.ino`.
   * Under **Tools $\rightarrow$ Board**, select **Arduino Leonardo** (or **Arduino Micro**).
   * Select your board's COM port under **Tools $\rightarrow$ Port**.
   * Click **Upload**.

---

## Repository Structure
* `/hardware`: Schematic PDF and hardware pinout map.
* `/firmware`: Complete Arduino HID source code.
Click Commit changes... $\rightarrow$ Commit changes.Step 2: Create hardware/pinout.mdClick Add file $\rightarrow$ Create new file.Type in the box:Plaintexthardware/pinout.md
Paste the verified V2 pinout table:Markdown# MicroPad V2 - Hardware Pinout Reference

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
