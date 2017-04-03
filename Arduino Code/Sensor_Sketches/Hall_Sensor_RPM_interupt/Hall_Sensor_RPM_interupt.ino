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
const int hallPin = 2;     // the number of the hall effect sensor pin
const int ledPin =  13;     // the number of the LED pin
// variables will change:
int hallState = 0;          // variable for reading the hall sensor status
int i = 0;
unsigned long t;            //time variables
unsigned long cur_t=0;      // cur_t is defaulted to 0
unsigned long t_diff;
float rpm;

void setup() {
  // initialize the LED pin as an output:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      
  // initialize the hall effect sensor pin as an input:
  pinMode(hallPin, INPUT);  
   attachInterrupt (digitalPinToInterrupt(hallPin), Anenometer_Rev, RISING);  // attach interrupt handler   
}

void loop(){
 delay(2000);
    Serial.print("rpm is: ");
    Serial.println(rpm);                    //print the rpm
    Serial.print("time per revolution: ");
    Serial.println(t_diff);
    Serial.print("number of revolutions: ");
    Serial.println(i);
}

void Anenometer_Rev(){
  if (t==0) {
    t=millis();
  }
  else {
    cur_t=millis();
    rpm = 1000.00*60/(cur_t-t);
    t_diff= cur_t-t;
    t=0;
  
  }
  i++;
}

