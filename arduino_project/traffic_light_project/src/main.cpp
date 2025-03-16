#include <Arduino.h>

#define RED_LED 9
#define YELLOW_LED 10
#define GREEN_LED 11
#define POT_PIN A0
#define BUTTON_1 2
#define BUTTON_2 3
#define BUTTON_3 4

int mode = 0;  // 0: 기본, 1: Emergency, 2: Blinking, 3: On/Off
bool systemOn = true;

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(BUTTON_3, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    if (digitalRead(BUTTON_1) == LOW) {
        mode = 1; // Emergency Mode
    }
    if (digitalRead(BUTTON_2) == LOW) {
        mode = 2; // Blinking Mode
    }
    if (digitalRead(BUTTON_3) == LOW) {
        mode = 3; // On/Off Mode
        systemOn = !systemOn;
    }

    int brightness = analogRead(POT_PIN) / 4; // 0~1023 → 0~255

    Serial.print("Mode: ");
    Serial.print(mode);
    Serial.print(", Brightness: ");
    Serial.println(brightness);

    if (!systemOn) {
        digitalWrite(RED_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        return;
    }

    switch (mode) {
        case 1: // Emergency Mode (Red LED only)
            analogWrite(RED_LED, brightness);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
            break;

        case 2: // Blinking Mode (All LEDs blink)
            analogWrite(RED_LED, brightness);
            analogWrite(YELLOW_LED, brightness);
            analogWrite(GREEN_LED, brightness);
            delay(500);
            digitalWrite(RED_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
            delay(500);
            break;

        default: // 기본 동작 (신호등)
            analogWrite(RED_LED, brightness);
            delay(2000);
            digitalWrite(RED_LED, LOW);
            analogWrite(YELLOW_LED, brightness);
            delay(500);
            digitalWrite(YELLOW_LED, LOW);
            analogWrite(GREEN_LED, brightness);
            delay(2000);
            digitalWrite(GREEN_LED, LOW);
            break;
    }
}