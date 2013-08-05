/*
  DeBounce
  Use a button to disable an LED while pressed
 
  This example code is in the public domain.
  Based on http://arduino.cc/en/Tutorial/Debounce
*/
int led = 11;
int button = 7;

void setup() {                
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
}

void toggleLED() {
  digitalWrite(led, !digitalRead(led));  
}

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void loop() {
  int reading = digitalRead(button);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        toggleLED();
      }
    }
  }
  
  lastButtonState = reading;
}
