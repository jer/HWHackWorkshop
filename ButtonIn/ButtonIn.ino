/*
  ButtonIn
  Use a button to disable an LED while pressed
 
  This example code is in the public domain.
*/
 
int led = 11;
int button = 7;

void setup() {                
  pinMode(led, OUTPUT);     
}

int intensity = 0x7F;
int increment = 1;

void loop() {
  int buttonState = digitalRead(button);
  
  while(buttonState == HIGH) {
    analogWrite(led, 0);
    delay(50);
    buttonState = digitalRead(button);
  }

  analogWrite(led, intensity);
  intensity += increment;
  if (intensity > 0xC0) increment = -1;
  if (intensity < 0x10) increment = 1;
  delay(10);
}
