unsigned long time;

void setup(){
  Serial.begin(9600);
}
void loop(){

  //prints time since program started
  time = micros();
  Serial.print("time in microseconds:  ");
  Serial.println(time);
  time = millis();
  Serial.print("time in Milliseconds:  ");
  Serial.println(time);
  // wait a second so as not to send massive amounts of data
  delay(1000);
}
