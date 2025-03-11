// Pin Definitions
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5

#define BTN1 6
#define BTN2 7
#define BTN3 8
#define BTN4 9

#define BUZZER 10

// Game Variables
int sequence[50]; // Stores the LED sequence
int level = 1;      // Starting game level

// Mapping LEDs and Buttons to Arrays for Cleaner Code
const int leds[] = {LED1, LED2, LED3, LED4};
const int buttons[] = {BTN1, BTN2, BTN3, BTN4};

void setup() {
    // Initialize LEDs
    for (int i = 0; i < 4; i++) {
        pinMode(leds[i], OUTPUT);
        digitalWrite(leds[i], HIGH); // Turn LEDs OFF (common anode logic)
    }

    // Initialize Buttons
    for (int i = 0; i < 4; i++) {
        pinMode(buttons[i], INPUT_PULLUP); // Uses internal pull-up resistors
    }

    // Initialize Buzzer
    pinMode(BUZZER, OUTPUT);

    // Random seed for generating unpredictable sequences
    randomSeed(analogRead(0));

    // Start Game
    Serial.begin(9600);
    Serial.println("Memory Game Starting!");
}

void loop() {
    generateSequence();   // Create a random sequence
    showSequence();       // Display sequence with LEDs

    if (!getPlayerInput()) {
        gameOver();       // Incorrect input triggers Game Over
    } else {
        level++;          // Advance to the next level if correct
        delay(1000);      // Brief pause before the next sequence
    }
}

// ------------------------- GAME LOGIC -------------------------

void generateSequence() {
    for (int i = 0; i < level; i++) {
        sequence[i] = random(1, 5);  // Random number between 1-4
    }
}

void showSequence() {
    for (int i = 0; i < level; i++) {
        lightLED(sequence[i]);
        delay(random(300, 700)); // Random delay for added challenge
        turnOffLEDs();
        delay(300);
    }
}

bool getPlayerInput() {
    for (int i = 0; i < level; i++) {
        int btnPressed = readButton();

        if (btnPressed == 0 || btnPressed != sequence[i]) {
            return false; // Incorrect input
        }

        // ✅ Buzzer Beeps for Each Correct Press
        tone(BUZZER, 1000, 200); // 1000Hz tone for 200ms
        delay(300);  // Prevent accidental double press
    }
    return true;
}

// ------------------------- BUTTON & LED CONTROL -------------------------

int readButton() {
    while (true) {
        for (int i = 0; i < 4; i++) {
            if (!digitalRead(buttons[i])) {
                delay(50); // Debounce delay
                if (!digitalRead(buttons[i])) {
                    return i + 1;  // Return button number (1-4)
                }
            }
        }
    }
}

void lightLED(int led) {
    digitalWrite(leds[led - 1], LOW); // LOW for common anode LED setup
}

void turnOffLEDs() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], HIGH); // Turn all LEDs OFF
    }
}

// ------------------------- GAME OVER LOGIC -------------------------

void gameOver() {
    Serial.println("Game Over! Restarting...");

    // Flash all LEDs and buzzer for Game Over effect
    for (int i = 0; i < 3; i++) {
        tone(BUZZER, 500, 300);
        for (int j = 0; j < 4; j++) {
            digitalWrite(leds[j], LOW); // Turn all LEDs ON
        }
        delay(300);

        turnOffLEDs();
        delay(300);
    }

    noTone(BUZZER); // Stop buzzer sound
    level = 1;      // Reset the game
    delay(2000);    // Brief pause before restarting
}
