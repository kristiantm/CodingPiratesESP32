#define BUTTON_LEFT_UP 25
#define BUTTON_LEFT_DOWN 27
#define JOYSTICK_RIGHT 15

void setup() {
  Serial.begin(9600);
  
  // Initialize buttons
  pinMode(BUTTON_LEFT_UP, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_DOWN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(BUTTON_LEFT_UP));
  Serial.println(digitalRead(BUTTON_LEFT_DOWN));
  Serial.println(analogRead(JOYSTICK_RIGHT));
  delay(1000);

}
