# Hardware Pinout & Specs

## Core Specs
* **Microcontroller:** Microchip ATmega32U4 (8-bit AVR, 16 MHz)
* **USB Interface:** Native Full-Speed USB 2.0 via USB-C
* **Operating Voltage:** 5V DC (Bus powered)
* **Dimensions:** 128.4 mm x 70.5 mm (2 Layers, 1.6 mm FR4)

---

## Pinout Map

| Physical Control | Pin / Channel | Type | Notes |
| :--- | :--- | :--- | :--- |
| **Joystick X-Axis** | `A0` | Analog In | 0–1023 range, center ~512 |
| **Joystick Y-Axis** | `A1` | Analog In | 0–1023 range, center ~512 |
| **Joystick Push (SEL)**| `D7` | Digital In | Active LOW (`INPUT_PULLUP`) |
| **Potentiometer** | `A5` | Analog In | 0–1023 linear sweep |
| **Tactile Button 1** | `D0` / `RX` | Digital In | Active LOW (`INPUT_PULLUP`) |
| **Tactile Button 2** | `D1` / `TX` | Digital In | Active LOW (`INPUT_PULLUP`) |
| **Tactile Button 3** | `D2` / `SDA` | Digital In | Active LOW (`INPUT_PULLUP`) |
| **Tactile Button 4** | `D3` / `SCL` | Digital In | Active LOW (`INPUT_PULLUP`) |
| **Board Status LED** | `D8` | Digital Out | Active HIGH |
