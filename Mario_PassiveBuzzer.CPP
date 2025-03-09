int melody[] = {
    2637, 2637, 0, 2637,   // E7, E7, Pause, E7
    0, 2093, 2637, 0,      // Pause, C7, E7, Pause
    3136, 0, 0, 0,         // G7, Pause, Pause, Pause
    1568, 0, 0, 0,         // G6, Pause, Pause, Pause

    2093, 0, 0, 1568,      // C7, Pause, Pause, G6
    0, 0, 1319, 0,         // Pause, Pause, E6, Pause
    0, 1760, 0, 1976,      // Pause, A6, Pause, B6
    0, 1760, 0, 1568       // Pause, A6, Pause, G6
};

int noteDurations[] = {
    100, 100, 100, 100,
    100, 100, 100, 100,
    100, 100, 100, 100,
   100, 100, 100, 100,

   100, 100, 100, 100,
    100, 100, 100, 100,
    100, 100, 100, 100,
   100, 100, 100, 100
};

void setup() {
    pinMode(8, OUTPUT);  // Passive buzzer connected to pin 8
}

void loop() {
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        if (melody[i] == 0) {
            delay(noteDurations[i]);  // Pause for silence
        } else {
            tone(8, melody[i], noteDurations[i]); // Play note
        }
        delay(noteDurations[i] * 1.1);  // Slight delay for smoother sound
        noTone(8);                      // Stop tone before the next note
    }

    delay(2000); // Pause before repeating the tune
}
