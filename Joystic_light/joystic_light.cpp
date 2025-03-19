int xpin = 0;
int ypin = 1;
int btnpin = 2;
int led_f = 3;
int led_b = 5;
int led_r = 6;
int led_l = 9;

const int DEAD_ZONE = 20; // Ignore minor fluctuations

void setup() {
  Serial.begin(9600);
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(btnpin, INPUT_PULLUP);
  pinMode(led_f, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(led_l, OUTPUT);
}

void loop() {
  int x = analogRead(xpin);
  int y = analogRead(ypin);
  int btnstate = digitalRead(btnpin);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print("  | Y: ");
  Serial.print(y);
  Serial.print("  | Button: ");
  Serial.println(btnstate);

  // Default brightness values
  int br_f = 0, br_b = 0, br_l = 0, br_r = 0;

  // Map brightness based on joystick movement intensity
  if (y < 510 - DEAD_ZONE) {
    br_f = map(y, 510 - DEAD_ZONE, 0, 0, 255);
  } 
  else if (y > 510 + DEAD_ZONE) {
    br_b = map(y, 510 + DEAD_ZONE, 1023, 0, 255);
  } 
  else if (x > 517 + DEAD_ZONE) {
    br_l = map(x, 517 + DEAD_ZONE, 1023, 0, 255);
  } 
  else if (x < 517 - DEAD_ZONE) {
    br_r = map(x, 517 - DEAD_ZONE, 0, 0, 255);
  }

  // Apply brightness using PWM
  analogWrite(led_f, br_f);
  analogWrite(led_b, br_b);
  analogWrite(led_l, br_l);
  analogWrite(led_r, br_r);

  delay(50);
}
