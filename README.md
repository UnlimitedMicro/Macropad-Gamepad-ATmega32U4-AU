# Custom ATmega32U4 USB Controller / Macropad (V1)

Welcome to the official repository! This board is an ATmega32U4-powered USB HID controller featuring an analog thumbstick, dual rotary encoders, a potentiometer, and tactile switches.

---

##  Video Tutorial
Need a step-by-step setup guide?  
👉 **[Watch the YouTube Setup & Programming Guide](YOUR_YOUTUBE_LINK_HERE)**

---

##  Quick Start Guide

### 1. Arduino IDE Setup
1. Download and install the latest **[Arduino IDE](https://www.arduino.cc/en/software)**.
2. Go to **Tools > Board > Arduino AVR Boards** and select **Arduino Leonardo** (or **Arduino Micro**).
3. Connect your board to your computer using a USB-C data cable.
4. Select the corresponding COM port under **Tools > Port**.

### 2. Flashing the Starter Code
1. Open `firmware/starter_test/starter_test.ino`.
2. Click **Upload** (the checkmark/arrow icon).
3. Open the **Serial Monitor** at **115200 baud** to see real-time inputs from buttons, encoders, and the joystick.

---

##  Hardware Pinout Reference

| Component | Function / Pin | Active State |
| :--- | :--- | :--- |
| **Joystick X-Axis** | Pin `A0` | Analog (0–1023) |
| **Joystick Y-Axis** | Pin `A1` | Analog (0–1023) |
| **Joystick Button (SEL)** | Pin `7` | Active LOW (`INPUT_PULLUP`) |
| **Potentiometer** | Pin `A5` | Analog (0–1023) |
| **Push Buttons (SW1–SW4)**| Pins `0, 1, 2, 3` | Active LOW (`INPUT_PULLUP`) |
| **Status LED** | Pin `8` | Active HIGH |

---

##  Repository Contents
* `/firmware`: Starter test sketch and HID keyboard/gamepad examples.
* `/hardware`: Schematic PDFs, component bill of materials (BOM), and pinout charts.