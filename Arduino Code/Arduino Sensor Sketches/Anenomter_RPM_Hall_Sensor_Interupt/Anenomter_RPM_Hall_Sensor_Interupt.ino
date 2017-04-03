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

const int wind_hallPin = 2;     // the number of the hall effect sensor pin
unsigned long wind_t;            //time variable for the anenometer
unsigned long wind_cur_t=0;      // cur_t is defaulted to 0
unsigned long wind_t_diff;      // time for one revolution of the anonometer
unsigned long wind_num_revs=0; 
float rpm;                      // RPM of the Anenometer

void setup() {
  Serial.begin(9600);
  pinMode(wind_hallPin, INPUT);  
  // attach interrupt handler:
  attachInterrupt (digitalPinToInterrupt(wind_hallPin), Anenometer_Rev, RISING);     
}

void loop(){
 delay(2000);
    Serial.print("rpm is: ");
    Serial.println(rpm);                    //print the rpm
    Serial.print("time per revolution: ");
    Serial.println(wind_t_diff);
    Serial.print("number of revolutions: ");
    Serial.println(wind_num_revs);
}

void Anenometer_Rev(){
  if (wind_t==0) {
    wind_t=millis();
  }
  else {
    wind_cur_t=millis();
    wind_t_diff= wind_cur_t - wind_t;
    rpm = 1000.00*60/wind_t_diff;
    wind_t=0;
  
  }
  wind_num_revs++;
}


