// http://arduinomodules.info/ky-003-hall-magnetic-sensor-module/

/*-----( Declare Variables )-----*/

#define ANENOMETER_HALL_PIN  A0
unsigned long t,cur_t;//time variables
 int refsig=200;//for converting the analog signal coming from hall sensor to digital through arduino code
 int val;//the digital value of the incoming analog signals
 int prev_val=0;
 float rpm;
 
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
// Nothing  (Stepper Library sets pins as outputs)
  Serial.begin(115200);
  t = 1000; // initial time value
  pinMode(A0,INPUT);
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
   rpm = (long)getRPM(ANENOMETER_HALL_PIN);
}/* --(end main loop )-- */

/* ( THE END ) */


long getRPM(int HALL_PIN) {
   cur_t = micros();

  int sig=analogRead(HALL_PIN);//read raw value of hall sensor
  if(sig>refsig) val=HIGH;//convert it to digital 0,1 form
  else val=LOW;
  if(prev_val==0 && val==1) {//check for rising edge
    
    Serial.print("rpm is: ");
    rpm = 1000000.00*60/(cur_t-t);
    Serial.println(rpm);//print the rpm
    Serial.print("time per revolution: ");
    Serial.println(cur_t-t);
    t=micros();
  }
   prev_val=val;
  return(rpm);
}


