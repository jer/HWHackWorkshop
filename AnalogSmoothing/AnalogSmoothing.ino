/*
  AnalogSmoothing
  Smooth an analog signal to toggle an LED
  Also outputs values over serial for graphing
 
  This example code is in the public domain.
  Based on http://arduino.cc/en/Tutorial/Graph
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

long inputSum = 0;
int inputCount = 0;

const int TRIGGERTHRESHOLD = 100;

void outputSerial(char whichReading, int reading) {
  Serial.print(whichReading);
  Serial.print(':');
  Serial.println(reading);
}

int calcNewAverage(int currentReading) {
  inputSum += currentReading;
  inputCount++;
  int average = inputSum / inputCount;
  
  if (inputCount > 10) {
    inputSum -= average;
    inputCount = 10;
  }
  return average;
}

void loop() {
  int reading = digitalRead(button);
  int analogReading = analogRead(photocell);
  int inputAverage = 0;

  outputSerial('a', analogReading);
  inputAverage = calcNewAverage(analogReading);

  outputSerial('b', inputAverage);

  if (analogReading > (inputAverage + TRIGGERTHRESHOLD)) {
    digitalWrite(led, HIGH);
  } else if (analogReading < (inputAverage - TRIGGERTHRESHOLD)) {
    digitalWrite(led, LOW);
  }

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
  delay(50);  // Just to help the serial port keep up
}
