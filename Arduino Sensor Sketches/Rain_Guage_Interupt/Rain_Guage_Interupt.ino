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
const int rain_hallPin = 3;     // the number of the hall effect sensor pin

// variables will change:
unsigned long bucket_tips = 0;
unsigned long t,cur_t;//time variables
void setup() {
  Serial.begin(9600);
  // initialize the hall effect sensor pin as an input:
  pinMode(rain_hallPin, INPUT);  
   attachInterrupt (digitalPinToInterrupt(rain_hallPin), rainBucketTip, RISING);  // attach interrupt handler   
}

void loop(){
 Serial.println(bucket_tips);
 Serial.println(t);
 delay(500);
}

void rainBucketTip(){
  t=millis();
  bucket_tips++;
}

