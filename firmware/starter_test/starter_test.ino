/*
 * Custom ATmega32U4 USB Controller - Hardware Test Sketch
 * Board setting in Arduino IDE: "Arduino Leonardo" or "Arduino Micro"
 * Baud Rate: 115200
 */

// Pin Definitions
const int JOY_X_PIN = A0;
const int JOY_Y_PIN = A1;
const int JOY_SW_PIN = 7;
const int POT_PIN    = A5;
const int BTN1_PIN   = 0;
const int BTN2_PIN   = 1;
const int BTN3_PIN   = 2;
const int BTN4_PIN   = 3;
const int LED_PIN    = 8;

void setup() {
  Serial.begin(115200);

  // Configure digital inputs with internal pull-up resistors
  pinMode(JOY_SW_PIN, INPUT_PULLUP);
  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);
  pinMode(BTN3_PIN, INPUT_PULLUP);
  pinMode(BTN4_PIN, INPUT_PULLUP);

  // Status LED Output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Turn LED on at boot
}

void loop() {
  // Read analog sensors (0 - 1023)
  int xVal   = analogRead(JOY_X_PIN);
  int yVal   = analogRead(JOY_Y_PIN);
  int potVal = analogRead(POT_PIN);

  // Read active-low buttons (LOW = pressed, HIGH = released)
  bool joyBtn = (digitalRead(JOY_SW_PIN) == LOW);
  bool b1     = (digitalRead(BTN1_PIN) == LOW);
  bool b2     = (digitalRead(BTN2_PIN) == LOW);
  bool b3     = (digitalRead(BTN3_PIN) == LOW);
  bool b4     = (digitalRead(BTN4_PIN) == LOW);

  // Print readable values to Serial Monitor
  Serial.print("Joy: (");
  Serial.print(xVal);
  Serial.print(", ");
  Serial.print(yVal);
  Serial.print(") | Pot: ");
  Serial.print(potVal);
  Serial.print(" | Buttons: [SW:");
  Serial.print(joyBtn);
  Serial.print(" B1:");
  Serial.print(b1);
  Serial.print(" B2:");
  Serial.print(b2);
  Serial.print(" B3:");
  Serial.print(b3);
  Serial.print(" B4:");
  Serial.print(b4);
  Serial.println("]");

  delay(50); // Refresh ~20 times a second
}
