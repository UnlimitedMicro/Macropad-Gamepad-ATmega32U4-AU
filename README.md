# MicroPad - Dual Rotary & Analog USB Controller

MicroPad is an open-source, programmable USB HID macro pad and custom input deck powered by the **ATmega32U4**. It provides native plug-and-play USB input across Windows, macOS, and Linux without needing any third-party drivers.

---

## Key Hardware Features

* **Dual EC11 Rotary Encoders:** Dedicated hardware dials for volume control, timeline scrubbing, zoom, or brush sizing with integrated push-click switches.
* **Analog Thumbstick:** Smooth 2-axis analog control with push-button click for mouse emulation or direct gamepad mapping.
* **4 Mechanical Key Switch Footprints (SW1–SW4):** Standard MX-compatible switch slots for ultra-responsive hotkeys and macros.
* **Integrated Slide Potentiometer (RV1):** Smooth linear fader for dynamic canvas zooming, timeline navigation, or audio volume.
* **Hardware Mode Switcher (SW8):** 3-position SP3T slider switch on the PCB to instantly toggle between **Game Mode**, **Mac Mode**, and **Windows Mode** on the fly.
* **Hardware Protection:** Full USB-C interface with ESD suppression (USBLC6-2SC6) and a 500mA PTC resettable fuse.

---

## Hardware Mode Switcher Functions

| Switch Position | Active Mode | SW1 | SW2 | SW3 | SW4 |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Left** | **Game Mode** | `Q` (Skill) | `E` (Interact) | `Left Shift` (Sprint) | `Space` (Jump) |
| **Center** | **Mac Mode** | `⌘ + Z` (Undo) | `⌘ + C` (Copy) | `⌘ + V` (Paste) | `Space` (Play/Pause) |
| **Right** | **Windows Mode** | `Ctrl + Z` (Undo) | `Ctrl + C` (Copy) | `Ctrl + V` (Paste) | `Space` (Play/Pause) |

---

## Quick Setup & Flashing

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

* `/hardware`: Schematic PDF and full hardware pinout documentation.
* `/firmware`: Complete Arduino HID source code.
