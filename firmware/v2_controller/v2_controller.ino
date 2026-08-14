/*
 * =====================================================================
 * MicroPad - Dual-Mode USB & Wireless Controller Firmware
 * Board: Arduino Leonardo or Arduino Micro (ATmega32U4 @ 16MHz, 5V)
 * Schematic: joystickstuff.kicad_sch
 * 
 * Required Libraries:
 *   1. "HID-Project" by NicoHood (Library Manager)
 *   2. "Encoder" by Paul Stoffregen (Library Manager)
 * =====================================================================
 */

#include <HID-Project.h>
#include <Encoder.h>

// ================= EXACT HARDWARE PIN DEFINITIONS =================

// 1. Analog Inputs
const int PIN_JOY_X   = A4;   // U1 H1 (PF1, Pin 40)
const int PIN_JOY_Y   = A5;   // U1 V1 (PF0, Pin 41)
const int PIN_POT     = A3;   // RV1 Slide Potentiometer Wiper (PF4, Pin 39)

// 2. Tactile Mechanical Key Switches (Active LOW)
const int PIN_BTN1    = 17;   // SW1 (PB0, Pin 8)
const int PIN_BTN2    = 15;   // SW2 (PB1, Pin 9)
const int PIN_BTN3    = 16;   // SW3 (PB2, Pin 10)
const int PIN_BTN4    = 14;   // SW4 (PB3, Pin 11)

// 3. Joystick Push Switch
const int PIN_JOY_SW  = 6;    // U1 SEL+ (PD7, Pin 27)

// 4. Hardware Mode Switcher (SW8 - SP3T)
const int PIN_MODE_A  = 9;    // SW8 Pin 1 (PB5, Pin 29) -> Game Mode
const int PIN_MODE_B  = 10;   // SW8 Pin 4 (PB6, Pin 30) -> Windows Mode
// Center Position (Both HIGH) -> Mac Mode

// 5. Rotary Encoders (SW6 & SW7)
const int ENC1_A      = 3;    // SW6 Pin A (PD0, Pin 18 - INT0)
const int ENC1_B      = 2;    // SW6 Pin B (PD1, Pin 19 - INT1)
const int ENC1_SW     = 5;    // SW6 Push (Moved to Pin 5 / PC6 to free UART)

const int ENC2_A      = 7;    // SW7 Pin A (Moved to Pin 7 / PE6 to free UART)
const int ENC2_B      = 4;    // SW7 Pin B (PD4, Pin 25)
const int ENC2_SW     = 12;   // SW7 Push (PD6, Pin 26)

// 6. Board Status Indicator LED
const int PIN_LED     = 8;    // D1 (PB4, Pin 28)

// ================= OBJECTS & STATE VARIABLES =================

Encoder knobVol(ENC1_A, ENC1_B);
Encoder knobScrub(ENC2_A, ENC2_B);

long lastVolPos    = -999;
long lastScrubPos  = -999;
int  lastPotVal    = 0;

const int JOY_CENTER = 512;
const int DEADZONE   = 45;
const int MOUSE_MAX  = 8;

// Debouncing state variables
bool lastJoySw  = HIGH;
bool lastEnc1Sw = HIGH;
bool lastEnc2Sw = HIGH;
bool lastBtn1   = HIGH;
bool lastBtn2   = HIGH;
bool lastBtn3   = HIGH;
bool lastBtn4   = HIGH;

// ================= WIRELESS TELEMETRY HELPER =================
void sendWireless(char type, int val1, int val2 = 0) {
  Serial1.print(type);
  Serial1.print(',');
  Serial1.print(val1);
  Serial1.print(',');
  Serial1.println(val2);
}

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

  // Read initial fader position
  lastPotVal = analogRead(PIN_POT);

  // Initialize Native USB HID Interfaces
  Consumer.begin();
  Keyboard.begin();
  Mouse.begin();

  // Initialize Hardware UART Coprocessor Link (Pins 0 & 1)
  Serial1.begin(115200);
}

void loop() {
  // -------------------------------------------------------------------
  // 1. ROTARY ENCODER 1: Media Volume Control & Mute Toggle
  // -------------------------------------------------------------------
  long curVolPos = knobVol.read() / 4;
  if (curVolPos > lastVolPos) {
    Consumer.write(MEDIA_VOLUME_UP);
    sendWireless('V', 1);
    lastVolPos = curVolPos;
  } else if (curVolPos < lastVolPos) {
    Consumer.write(MEDIA_VOLUME_DOWN);
    sendWireless('V', -1);
    lastVolPos = curVolPos;
  }

  bool curEnc1Sw = digitalRead(ENC1_SW);
  if (curEnc1Sw == LOW && lastEnc1Sw == HIGH) {
    Consumer.write(MEDIA_VOLUME_MUTE);
    sendWireless('V', 0); // 0 = Mute toggle
    delay(15);
  }
  lastEnc1Sw = curEnc1Sw;

  // -------------------------------------------------------------------
  // 2. ROTARY ENCODER 2: Timeline Scrub / Vertical Scroll & Enter
  // -------------------------------------------------------------------
  long curScrubPos = knobScrub.read() / 4;
  if (curScrubPos > lastScrubPos) {
    Mouse.move(0, 0, 1);
    sendWireless('S', 1);
    lastScrubPos = curScrubPos;
  } else if (curScrubPos < lastScrubPos) {
    Mouse.move(0, 0, -1);
    sendWireless('S', -1);
    lastScrubPos = curScrubPos;
  }

  bool curEnc2Sw = digitalRead(ENC2_SW);
  if (curEnc2Sw == LOW && lastEnc2Sw == HIGH) {
    Keyboard.write(KEY_RETURN);
    sendWireless('K', '\n');
    delay(15);
  }
  lastEnc2Sw = curEnc2Sw;

  // -------------------------------------------------------------------
  // 3. SLIDE POTENTIOMETER: Dynamic Zoom / Brush Size (Ctrl + Scroll)
  // -------------------------------------------------------------------
  int curPotVal = analogRead(PIN_POT);
  int potDiff   = curPotVal - lastPotVal;
  if (abs(potDiff) > 35) {
    Keyboard.press(KEY_LEFT_CTRL);
    if (potDiff > 0) {
      Mouse.move(0, 0, 1);
      sendWireless('Z', 1);
    } else {
      Mouse.move(0, 0, -1);
      sendWireless('Z', -1);
    }
    delay(10);
    Keyboard.release(KEY_LEFT_CTRL);
    lastPotVal = curPotVal;
  }

  // -------------------------------------------------------------------
  // 4. ANALOG JOYSTICK: Cursor Navigation & Left Click
  // -------------------------------------------------------------------
  int xRaw = analogRead(PIN_JOY_X) - JOY_CENTER;
  int yRaw = analogRead(PIN_JOY_Y) - JOY_CENTER;
  int moveX = 0;
  int moveY = 0;

  if (abs(xRaw) > DEADZONE) moveX = map(xRaw, -512, 512, -MOUSE_MAX, MOUSE_MAX);
  if (abs(yRaw) > DEADZONE) moveY = map(yRaw, -512, 512, MOUSE_MAX, -MOUSE_MAX);

  if (moveX != 0 || moveY != 0) {
    Mouse.move(moveX, moveY, 0);
    sendWireless('M', moveX, moveY);
  }

  bool curJoySw = digitalRead(PIN_JOY_SW);
  if (curJoySw == LOW && lastJoySw == HIGH) {
    Mouse.press(MOUSE_LEFT);
    sendWireless('C', 1);
  } else if (curJoySw == HIGH && lastJoySw == LOW) {
    Mouse.release(MOUSE_LEFT);
    sendWireless('C', 0);
  }
  lastJoySw = curJoySw;

  // -------------------------------------------------------------------
  // 5. HARDWARE MODE SWITCHER (SW8) & MECHANICAL KEY SWITCHES
  // -------------------------------------------------------------------
  bool modeGame = (digitalRead(PIN_MODE_A) == LOW);
  bool modeWin  = (digitalRead(PIN_MODE_B) == LOW);

  bool curBtn1 = digitalRead(PIN_BTN1);
  bool curBtn2 = digitalRead(PIN_BTN2);
  bool curBtn3 = digitalRead(PIN_BTN3);
  bool curBtn4 = digitalRead(PIN_BTN4);

  // ==========================================
  // MODE 1: GAME MODE (SW8 Left)
  // ==========================================
  if (modeGame) {
    if (curBtn1 == LOW && lastBtn1 == HIGH) { Keyboard.press('q'); sendWireless('P', 'q'); }
    else if (curBtn1 == HIGH && lastBtn1 == LOW) { Keyboard.release('q'); sendWireless('R', 'q'); }

    if (curBtn2 == LOW && lastBtn2 == HIGH) { Keyboard.press('e'); sendWireless('P', 'e'); }
    else if (curBtn2 == HIGH && lastBtn2 == LOW) { Keyboard.release('e'); sendWireless('R', 'e'); }

    if (curBtn3 == LOW && lastBtn3 == HIGH) { Keyboard.press(KEY_LEFT_SHIFT); sendWireless('P', 0x81); }
    else if (curBtn3 == HIGH && lastBtn3 == LOW) { Keyboard.release(KEY_LEFT_SHIFT); sendWireless('R', 0x81); }

    if (curBtn4 == LOW && lastBtn4 == HIGH) { Keyboard.press(' '); sendWireless('P', ' '); }
    else if (curBtn4 == HIGH && lastBtn4 == LOW) { Keyboard.release(' '); sendWireless('R', ' '); }
  }
  // ==========================================
  // MODE 2: WINDOWS MODE (SW8 Right)
  // ==========================================
  else if (modeWin) {
    if (curBtn1 == LOW && lastBtn1 == HIGH) {
      Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('z'); delay(10); Keyboard.releaseAll();
      sendWireless('W', 'z'); // Shortcut Undo
    }
    if (curBtn2 == LOW && lastBtn2 == HIGH) {
      Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('c'); delay(10); Keyboard.releaseAll();
      sendWireless('W', 'c'); // Shortcut Copy
    }
    if (curBtn3 == LOW && lastBtn3 == HIGH) {
      Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('v'); delay(10); Keyboard.releaseAll();
      sendWireless('W', 'v'); // Shortcut Paste
    }
    if (curBtn4 == LOW && lastBtn4 == HIGH) { Keyboard.press(' '); sendWireless('P', ' '); }
    else if (curBtn4 == HIGH && lastBtn4 == LOW) { Keyboard.release(' '); sendWireless('R', ' '); }
  }
  // ==========================================
  // MODE 3: MAC OS MODE (SW8 Center)
  // ==========================================
  else {
    if (curBtn1 == LOW && lastBtn1 == HIGH) {
      Keyboard.press(KEY_LEFT_GUI); Keyboard.press('z'); delay(10); Keyboard.releaseAll();
      sendWireless('A', 'z'); // Mac Undo
    }
    if (curBtn2 == LOW && lastBtn2 == HIGH) {
      Keyboard.press(KEY_LEFT_GUI); Keyboard.press('c'); delay(10); Keyboard.releaseAll();
      sendWireless('A', 'c'); // Mac Copy
    }
    if (curBtn3 == LOW && lastBtn3 == HIGH) {
      Keyboard.press(KEY_LEFT_GUI); Keyboard.press('v'); delay(10); Keyboard.releaseAll();
      sendWireless('A', 'v'); // Mac Paste
    }
    if (curBtn4 == LOW && lastBtn4 == HIGH) { Keyboard.press(' '); sendWireless('P', ' '); }
    else if (curBtn4 == HIGH && lastBtn4 == LOW) { Keyboard.release(' '); sendWireless('R', ' '); }
  }

  lastBtn1 = curBtn1;
  lastBtn2 = curBtn2;
  lastBtn3 = curBtn3;
  lastBtn4 = curBtn4;

  delay(5); // ~200Hz polling rate
}
