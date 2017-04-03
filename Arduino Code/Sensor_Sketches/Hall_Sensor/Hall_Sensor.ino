/*
 Hall Effect Switch
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when Hall Effect Sensor attached to pin 2 is triggered by a magnet
 
 Hall effect sensor used is the A1120EUA from Allegro Microsystems
 
 This example code is in the public domain.
 
http://www.hobbytronics.co.uk/arduino-tutorial11-hall-effect

// the pic shows the circuit layout of the complete hall sensor module: 
// http://3.bp.blogspot.com/-lgVEMtJ1Iu0/VlZDfs0jLDI/AAAAAAAAGJ8/MEHhEO7kQbo/s1600/37in1_HallSensorKY003.png
 
*/

// constants won't change. They're used here to set pin numbers:
const int hallPin = 3;     // the number of the hall effect sensor pin
const int ledPin =  13;     // the number of the LED pin
// variables will change:
int hallState = 0;          // variable for reading the hall sensor status

void setup() {
  // initialize the LED pin as an output:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
  // initialize the hall effect sensor pin as an input:
  pinMode(hallPin, INPUT);     
}

void loop(){
  // read the state of the hall effect sensor:
  hallState = digitalRead(hallPin);

  if (hallState == LOW) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);
    Serial.println("on"); 
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
   // Serial.println("off"); 
  }
}
