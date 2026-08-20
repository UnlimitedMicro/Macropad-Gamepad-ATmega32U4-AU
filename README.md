# MicroPad - Universal Dual-Encoder USB HID Controller
# Copyright (C) 2026 UnlimitedMicro / MicroPad Project
# This firmware is licensed under CC BY-NC-SA 4.0.
# Commercial use, reproduction, or sales are strictly prohibited.

MicroPad is an open-source, fully programmable macro pad and USB input controller powered by the **ATmega32U4**. It provides driverless, plug-and-play USB HID operation across Windows, macOS, and Linux.

---

## Features

* **Dual EC11 Rotary Encoders (`SW6`, `SW7`):** Hardware volume control and timeline scrub/scroll with integrated push-to-click buttons.
* **Analog Thumbstick (`U1`):** Smooth 2-axis mouse cursor navigation and left-click switch.
* **Integrated Slide Potentiometer (`RV1`):** Linear fader for zooming, canvas scaling, or brush resizing.
* **4 MX-Compatible Mechanical Switch Sockets (`SW1`–`SW4`):** Dedicated hotkey pads.
* **Hardware Profile Switcher (`SW8`):** 3-position SP3T slider switch on the PCB to switch profiles in real-time.
* **USB-C Interface:** Full ESD protection via USBLC6-2SC6 and a 500mA PTC resettable fuse.

---

## Hardware Mode Profiles (`SW8`)

| Switch Position | Active Mode | SW1 | SW2 | SW3 | SW4 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Left** | **Game Mode** | `Q` (Skill) | `E` (Interact) | `Left Shift` (Sprint) | `Space` (Jump) |
| **Center** | **Mac Mode** | `⌘ + Z` (Undo) | `⌘ + C` (Copy) | `⌘ + V` (Paste) | `Space` (Play/Pause) |
| **Right** | **Windows Mode** | `Ctrl + Z` (Undo) | `Ctrl + C` (Copy) | `Ctrl + V` (Paste) | `Space` (Play/Pause) |

---

## Flashing & Setup Guide

### 1. Burn the Bootloader (First Time Only)
Factory ATmega32U4 chips are blank and must have the bootloader flashed via the 6-pin ISP header (`J2`):

1. Connect an **Arduino Uno** running the `ArduinoISP` example sketch.
2. Insert a **100Ω resistor between 5V and RESET** on the Uno to prevent auto-reset.
3. Wire the Uno to the MicroPad ISP header:
   * Uno `Pin 11` $\rightarrow$ `MOSI`
   * Uno `Pin 12` $\rightarrow$ `MISO`
   * Uno `Pin 13` $\rightarrow$ `SCK`
   * Uno `Pin 10` $\rightarrow$ `RST`
   * Uno `5V`     $\rightarrow$ `5V`
   * Uno `GND`    $\rightarrow$ `GND`
4. In the Arduino IDE:
   * **Tools $\rightarrow$ Board $\rightarrow$ Arduino AVR Boards $\rightarrow$ Arduino Leonardo**
   * **Tools $\rightarrow$ Programmer $\rightarrow$ "Arduino as ISP"**
   * Select **Tools $\rightarrow$ Burn Bootloader**.

---

### 2. Upload Firmware (USB-C)
Once the bootloader is burned, disconnect the ISP programmer and plug the board in directly via USB-C:

1. Install required libraries in the Arduino Library Manager:
   * `HID-Project` by NicoHood
   * `Encoder` by Paul Stoffregen
2. Open `firmware/v2_controller/v2_controller.ino`.
3. Select **Tools $\rightarrow$ Board $\rightarrow$ Arduino Leonardo** and select your COM port.
4. Click **Upload**.
