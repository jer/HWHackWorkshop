/*
  Analog
  Read an analog signal in and write it out the serial port immediately
 
  This example code is in the public domain.
*/

int led = 11;
int button = 7;
int photocell = A0;

void setup() {                
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(photocell, INPUT);
  Serial.begin(9600);
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
  int analogReading = analogRead(photocell);
  int inputAverage = 0;

  Serial.println(analogReading);

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
  delay(250);  // Just to help the serial port keep up
}
