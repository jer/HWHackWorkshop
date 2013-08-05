/*
  Fade
  Fade an LED off and on using analogWrite
 
  This example code is in the public domain.
*/
 
int led = 11;

void setup() {                
  pinMode(led, OUTPUT);     
}

int intensity = 0x7F;
int increment = 1;

void loop() {
  analogWrite(led, intensity);
  intensity += increment;
  if (intensity > 0xC0) increment = -1;
  if (intensity < 0x10) increment = 1;
  delay(10);
}
