// Based on http://arduino.cc/en/Tutorial/Graph
// This example code is in the public domain.

import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph

void setup () {
  // set the window size:
  size(400, 600);        
  
  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
}

void draw () {
  // everything happens in the serialEvent()
}

void setColor(char c) {
  switch (c) {
    case 'a':
      stroke(127,34,255);
      break;
    case 'b':
      stroke(255,34,127);
      break;
  }
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    
    // trim off any whitespace:
    inString = trim(inString);

    if(!inString.matches("[a-z]:\\d+")) return;

    String[] inValues = inString.split(":");
    if(inValues == null) return;
    char whichReading = inValues[0].toCharArray()[0];

    // convert to an int and map to the screen height:
    float inByte = float(inValues[1]); 
    inByte = map(inByte, 0, 1023, 0, height);
    
    // draw the line:
    stroke(0);
    line(xPos, 0, xPos, height);
    setColor(whichReading);
    line(xPos, height - inByte - 2, xPos, height - inByte);
    
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
    } 
    else {
      // increment the horizontal position:
      xPos++;
    }
  }
}

