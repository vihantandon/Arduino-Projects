#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // LCD Pins: RS, E, D4, D5, D6, D7

#define BUTTON_PIN 2
#define LED_PIN 3
#define BUZZER_PIN 4

String morseInput = "";
String decodedText = "";
unsigned long pressStartTime = 0;
unsigned long lastPressTime = 0;
unsigned long lastLCDUpdate = 0;
bool buttonPressed = false;
bool resetTriggered = false;

const unsigned long debounceDelay = 50;   // Button debounce delay (ms)
const unsigned long decodeDelay = 2000;   // Time before decoding (ms)
const unsigned long resetHoldTime = 3000; // Hold button for 3s to reset
const unsigned long spaceDelay = 4000;    // Gap time to insert a space (ms)

const char* morseTable[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};
const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char decodeMorse(String morse) {
    for (int i = 0; i < 26; i++) {
        if (morse == morseTable[i]) return letters[i];
    }
    return '?';  // Unknown Morse input
}

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    lcd.begin(16, 2);
    Serial.begin(9600);  // Debugging
    lcd.setCursor(0, 0);
    lcd.print("Morse Code:");
    updateLCD();
}

void loop() {
    unsigned long currentTime = millis();
    bool buttonState = digitalRead(BUTTON_PIN) == LOW;

    // Handle Button Press (Debounce)
    static unsigned long lastDebounceTime = 0;
    static bool lastButtonState = HIGH;

    if (buttonState != lastButtonState) {
        lastDebounceTime = currentTime;
    }

    if ((currentTime - lastDebounceTime) > debounceDelay) {
        if (buttonState && !buttonPressed) {
            pressStartTime = currentTime;
            buttonPressed = true;
        }

        if (!buttonState && buttonPressed) { // Button released
            unsigned long pressDuration = currentTime - pressStartTime;
            buttonPressed = false;
            lastPressTime = currentTime;

            if (pressDuration >= resetHoldTime) {  // Reset if held for 3s
                resetMorseCode();
            } else if (pressDuration < 500) {  // Short press → "."
                morseInput += ".";
                blinkBuzzer(100);
            } else if (pressDuration >= 500) {  // Long press → "-"
                morseInput += "-";
                blinkBuzzer(300);
            }
            updateLCD();
        }
    }

    lastButtonState = buttonState;

    // Decode Morse after inactivity
    if (morseInput.length() > 0 && currentTime - lastPressTime > decodeDelay) {
        decodedText += decodeMorse(morseInput);
        morseInput = "";
        updateLCD();
    }

    // Add a space if no input for long time
    if (currentTime - lastPressTime > spaceDelay && morseInput.length() > 0) {
        decodedText += " ";
        lastPressTime = currentTime;
        updateLCD();
    }

    // LCD Refresh every 100ms to prevent lagging
    if (currentTime - lastLCDUpdate > 100) {
        updateLCD();
        lastLCDUpdate = currentTime;
    }
}

// Function to reset Morse code input
void resetMorseCode() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Resetting...");

    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, HIGH);
        tone(BUZZER_PIN, 1000);
        delay(200);
        digitalWrite(LED_PIN, LOW);
        noTone(BUZZER_PIN);
        delay(200);
    }

    morseInput = "";
    decodedText = "";
    updateLCD();
}

// Function to blink LED and sound buzzer
void blinkBuzzer(int duration) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
    delay(duration);
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
}

// **Fixed LCD update function**
void updateLCD() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Morse: ");
    lcd.print(morseInput);
    
    lcd.setCursor(0, 1);
    lcd.print("Text: ");
    lcd.print(decodedText);
}
