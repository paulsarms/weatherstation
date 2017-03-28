unsigned long t;

void setup(){
  Serial.begin(9600);
}
void loop(){

  //prints time since program started
  t = micros();
  Serial.print("time in microseconds:  ");
  Serial.println(t);
  t = millis();
  Serial.print("time in Milliseconds:  ");
  Serial.println(t);
  // wait a second so as not to send massive amounts of data
  delay(1000);
}

