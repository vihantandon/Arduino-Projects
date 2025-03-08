#define NUM_LEDS 10
int ledPins[NUM_LEDS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

void setup() {
    for(int i = 0; i < NUM_LEDS; i++) {
        pinMode(ledPins[i], OUTPUT);
    }
}

void blink_1()
{
  for(int i = 0; i < NUM_LEDS; i++) {
        if(i > 0) digitalWrite(ledPins[i - 1], LOW); 
        digitalWrite(ledPins[i], HIGH);  
        if(i < NUM_LEDS - 1) digitalWrite(ledPins[i + 1], HIGH);  
        if(i < NUM_LEDS - 2) digitalWrite(ledPins[i + 2], HIGH);  
        delay(100);
    }

    for(int i = NUM_LEDS - 1; i >= 0; i--) {
        if(i < NUM_LEDS - 1) digitalWrite(ledPins[i + 1], LOW); 
        digitalWrite(ledPins[i], HIGH); 
        if(i > 0) digitalWrite(ledPins[i - 1], HIGH); 
        if(i > 1) digitalWrite(ledPins[i - 2], HIGH); 
        delay(100);
    }
}

void blink_2()
{
  for(int i = 0; i < NUM_LEDS; i++) {
        digitalWrite(ledPins[i], HIGH);
        delay(100); 
    }

    delay(900);

    for(int i = 0; i < NUM_LEDS; i++) {
        digitalWrite(ledPins[i], LOW);
        delay(100);  
    }
}

void loop() {
    blink_1();

    blink_2();
}
