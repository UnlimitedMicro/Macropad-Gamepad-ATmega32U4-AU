/*
 * =====================================================================
 * MicroPad V2 - Dual Rotary Encoder & Analog USB Controller
 * Board: Arduino Leonardo (ATmega32U4 @ 16MHz, 5V)
 * Schematic: joystickstuff.kicad_sch
 * Required Libraries: "HID-Project" (by NicoHood), "Encoder" (by Paul Stoffregen)
 * =====================================================================
 */

#include <HID-Project.h>
#include <Encoder.h>

// ================= PIN DEFINITIONS =================
// 1. Analog Inputs
const int PIN_JOY_X   = A4;   // U1 H1 (PF1, Pin 40)
const int PIN_JOY_Y   = A5;   // U1 V1 (PF0, Pin 41)
const int PIN_POT     = A3;   // RV1 Wiper (PF4, Pin 39)

// 2. Digital Switches & Buttons (Active LOW)
const int PIN_JOY_SW  = 6;    // U1 SEL+ (PD7, Pin 27)
const int PIN_BTN1    = 17;   // SW1 (PB0, Pin 8)
const int PIN_BTN2    = 15;   // SW2 (PB1, Pin 9)
const int PIN_BTN3    = 16;   // SW3 (PB2, Pin 10)
const int PIN_BTN4    = 14;   // SW4 (PB3, Pin 11)

// 3. Mode Select Switch (SP3T)
const int PIN_MODE_A  = 9;    // SW8 Pin 1 (PB5, Pin 29)
const int PIN_MODE_B  = 10;   // SW8 Pin 4 (PB6, Pin 30)

// 4. Rotary Encoders (SW6 & SW7)
const int ENC1_A      = 3;    // SW6 Pin A (PD0, Pin 18 - INT0)
const int ENC1_B      = 2;    // SW6 Pin B (PD1, Pin 19 - INT1)
const int ENC1_SW     = 0;    // SW6 Push (PD2, Pin 20 - RX)

const int ENC2_A      = 1;    // SW7 Pin A (PD3, Pin 21 - TX)
const int ENC2_B      = 4;    // SW7 Pin B (PD4, Pin 25)
const int ENC2_SW     = 12;   // SW7 Push (PD6, Pin 26)

// 5. Status Indicator LED
const int PIN_LED     = 8;    // D1 (PB4, Pin 28)

// ================= OBJECTS & VARIABLES =================
Encoder knobVol(ENC1_A, ENC1_B);
Encoder knobScrub(ENC2_A, ENC2_B);

long lastVolPos   = -999;
long lastScrubPos = -999;

const int JOY_CENTER = 512;
const int DEADZONE   = 45;
const int MOUSE_MAX  = 8;

// Button state tracking for clean single-press triggering
bool lastJoySw  = HIGH;
bool lastEnc1Sw = HIGH;
bool lastEnc2Sw = HIGH;
bool lastBtn1   = HIGH;
bool lastBtn2   = HIGH;
bool lastBtn3   = HIGH;
bool lastBtn4   = HIGH;

void setup() {
  // Configure all inputs with internal pull-up resistors
  pinMode(PIN_JOY_SW, INPUT_PULLUP);
  pinMode(PIN_BTN1,   INPUT_PULLUP);
  pinMode(PIN_BTN2,   INPUT_PULLUP);
  pinMode(PIN_BTN3,   INPUT_PULLUP);
  pinMode(PIN_BTN4,   INPUT_PULLUP);
  pinMode(PIN_MODE_A, INPUT_PULLUP);
  pinMode(PIN_MODE_B, INPUT_PULLUP);
  pinMode(ENC1_SW,    INPUT_PULLUP);
  pinMode(ENC2_SW,    INPUT_PULLUP);

  // Status LED Output
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);

  // Initialize Native USB HID interfaces
  Consumer.begin();
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // -------------------------------------------------------------------
  // 1. ROTARY ENCODER 1 (SW6): Master Volume & Mute Toggle
  // -------------------------------------------------------------------
  long curVolPos = knobVol.read() / 4; // 4 pulses per physical detent
  if (curVolPos > lastVolPos) {
    Consumer.write(MEDIA_VOLUME_UP);
    lastVolPos = curVolPos;
  } else if (curVolPos < lastVolPos) {
    Consumer.write(MEDIA_VOLUME_DOWN);
    lastVolPos = curVolPos;
  }

  bool curEnc1Sw = digitalRead(ENC1_SW);
  if (curEnc1Sw == LOW && lastEnc1Sw == HIGH) {
    Consumer.write(MEDIA_VOLUME_MUTE);
    delay(10);
  }
  lastEnc1Sw = curEnc1Sw;

  // -------------------------------------------------------------------
  // 2. ROTARY ENCODER 2 (SW7): Scroll / Scrub & Enter
  // -------------------------------------------------------------------
  long curScrubPos = knobScrub.read() / 4;
  if (curScrubPos > lastScrubPos) {
    Mouse.move(0, 0, 1); // Scroll Up / Scrub Forward
    lastScrubPos = curScrubPos;
  } else if (curScrubPos < lastScrubPos) {
    Mouse.move(0, 0, -1); // Scroll Down / Scrub Backward
    lastScrubPos = curScrubPos;
  }

  bool curEnc2Sw = digitalRead(ENC2_SW);
  if (curEnc2Sw == LOW && lastEnc2Sw == HIGH) {
    Keyboard.write(KEY_RETURN);
    delay(10);
  }
  lastEnc2Sw = curEnc2Sw;

  // -------------------------------------------------------------------
  // 3. ANALOG JOYSTICK (U1): Cursor Movement & Left Click
  // -------------------------------------------------------------------
  int xRaw = analogRead(PIN_JOY_X) - JOY_CENTER;
  int yRaw = analogRead(PIN_JOY_Y) - JOY_CENTER;
  int moveX = 0;
  int moveY = 0;

  if (abs(xRaw) > DEADZONE) moveX = map(xRaw, -512, 512, -MOUSE_MAX, MOUSE_MAX);
  if (abs(yRaw) > DEADZONE) moveY = map(yRaw, -512, 512, MOUSE_MAX, -MOUSE_MAX);

  if (moveX != 0 || moveY != 0) {
    Mouse.move(moveX, moveY, 0);
  }

  bool curJoySw = digitalRead(PIN_JOY_SW);
  if (curJoySw == LOW && lastJoySw == HIGH) {
    Mouse.press(MOUSE_LEFT);
  } else if (curJoySw == HIGH && lastJoySw == LOW) {
    Mouse.release(MOUSE_LEFT);
  }
  lastJoySw = curJoySw;

  // -------------------------------------------------------------------
  // 4. TACTILE PUSHBUTTONS (SW1 - SW4): Productivity Shortcuts
  // -------------------------------------------------------------------
  // SW1: Undo (Ctrl + Z)
  bool curBtn1 = digitalRead(PIN_BTN1);
  if (curBtn1 == LOW && lastBtn1 == HIGH) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('z');
    delay(10);
    Keyboard.releaseAll();
  }
  lastBtn1 = curBtn1;

  // SW2: Copy (Ctrl + C)
  bool curBtn2 = digitalRead(PIN_BTN2);
  if (curBtn2 == LOW && lastBtn2 == HIGH) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('c');
    delay(10);
    Keyboard.releaseAll();
  }
  lastBtn2 = curBtn2;

  // SW3: Paste (Ctrl + V)
  bool curBtn3 = digitalRead(PIN_BTN3);
  if (curBtn3 == LOW && lastBtn3 == HIGH) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('v');
    delay(10);
    Keyboard.releaseAll();
  }
  lastBtn3 = curBtn3;

  // SW4: Spacebar (Play / Pause / Action)
  bool curBtn4 = digitalRead(PIN_BTN4);
  if (curBtn4 == LOW && lastBtn4 == HIGH) {
    Keyboard.press(' ');
  } else if (curBtn4 == HIGH && lastBtn4 == LOW) {
    Keyboard.release(' ');
  }
  lastBtn4 = curBtn4;

  delay(5); // Polling loop (~200Hz)
}
