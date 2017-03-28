/**
 * 
 * --- DSM501 SamYoung Dust Sensor    ---
 *   connect the sensor as follows :
 *        Pin 2 of dust sensor PM1  -> Digital 6 (PWM)
 *    Pin 3 of dust sensor          -> +5V 
 *    Pin 4 of dust sensor PM2.5    -> Digital 5 (PWM) 
 *    Pin 5 of dust sensor          -> Ground
 * Datasheet: http://www.samyoungsnc.com/products/3-1%20Specification%20DSM501.pdf
* 
*  --- DHT22 Temperature and Humidity Sensor ---
*   DHT22 pin 1   -> arduino GND
*   DHT22 pin 2   -> ardiuno 5v
*   DHT22 pin 3   -> arduino Digital pin 4
* 
* -- BMP180 Barometric Presure Sensor-- I'm using a Keyestudion BMP180. info here: http://www.keyestudio.cc/h-pd-106.html
// Connect VCC of the BMP180 sensor to 5V (or 3.3fv)
// Connect GND to Ground
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/Nano/etc thats Analog 4
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/Nano/etc thats Analog 5

 -- Anenometer Hall Sensor -- 
  This is the pin setup for a Keyes KY-003 Hall Effect Sensor
    Hall sensor Pin 1   ->  arduino GND
    Hall sensor Pin 2   ->  arduino 5v
    Hall sensor Pin 3   ->  arduino Digital pin 2 (must be either pin 2 or 3 which are the interupt pins)

-- Rain Guage Hall Sensor --
  This is the pin setup for a Keyes KY-003 Hall Effect Sensor
    Hall sensor Pin 1   ->  arduino GND
    Hall sensor Pin 2   ->  arduino 5v
    Hall sensor Pin 3   ->  arduino Digital pin 3 (must be either pin 2 or 3 which are the interupt pins)


Radio TX Data pin -> arduino digital pin 12


**/

// Libraries
#include <DHT.h>;
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include <VirtualWire.h>


// Constants
#define DUST_SENSOR_DIGITAL_PIN_PM10  6
#define DUST_SENSOR_DIGITAL_PIN_PM25  5
#define DHT22PIN 7     // what pin we're connected to
#define DHT_1_TYPE DHT22   // DHT 22  (AM2302)
DHT dht22(DHT22PIN, DHT_1_TYPE); //// Initialize DHT sensor for normal 16mhz Arduino
Adafruit_BMP085 bmp;
const int transmit_pin = 12;
const int wind_hallPin = 2;     // the number of the anenometer hall effect sensor pin
const int rain_hallPin = 3;     // the number of the rain guage hall effect sensor pin

//VARIABLES
int val = 0;           // variable to store the value coming from the sensor
float valDUSTPM25 =0.0;
float lastDUSTPM25 =0.0;
float valDUSTPM10 =0.0;
float lastDUSTPM10 =0.0;
unsigned long duration;
unsigned long starttime;
unsigned long endtime;
unsigned long sampletime_ms = 3000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
long concentrationPM25 = 0;
long concentrationPM10 = 0;
long concentration;
float ppmv;

float  dht22_hum;  //Stores dht22 humidity value
float dht22_temp; //Stores dht22 temperature value
float bmp_180_temp; //Stores bmp180 temperature value
float bmp_180_presure; //Stores bmp180 pressure value
String output;

unsigned long wind_t;            //time variable for the anenometer
unsigned long wind_cur_t=0;      // cur_t is defaulted to 0
unsigned long wind_t_diff;      // time for one revolution of the anonometer
unsigned long wind_num_revs=0; 
volatile float rpm;                      // RPM of the Anenometer
volatile int bucket_tips = 1;  // Number of Rain Guage bucket tips


void setup()  
{
  Serial.begin(9600);
  dht22.begin();
  bmp.begin();
  vw_set_tx_pin(transmit_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000); // Bits per sec

  pinMode(wind_hallPin, INPUT); 
  pinMode(rain_hallPin, INPUT);  
  // attach interrupt handler for the Anenometer hall sensor:
  attachInterrupt (digitalPinToInterrupt(wind_hallPin), Anenometer_Rev, RISING);  
  // attach interrupt handler for the Rain Guage hall sensor:
  attachInterrupt (digitalPinToInterrupt(rain_hallPin), rainBucketTip, RISING);  
}

void loop()      
{    
  
  /* START Code for DSM501 Dust Sensor reading */
    //get PM 2.5 density of particles over 2.5 μm.
    concentrationPM25=(long)getPM(DUST_SENSOR_DIGITAL_PIN_PM25);
  
  
    if ((concentrationPM25 != lastDUSTPM25)&&(concentrationPM25>0)) {
        lastDUSTPM25 = ceil(concentrationPM25);
    }
   //get PM 1.0 - density of particles over 1 μm.
  
   
    concentrationPM10=getPM(DUST_SENSOR_DIGITAL_PIN_PM10);
  
    //ppmv=mg/m3 * (0.08205*Tmp)/Molecular_mass
    //0.08205   = Universal gas constant in atm·m3/(kmol·K)
    ppmv=(float)(((concentrationPM25*0.0283168)/100) *  ((0.08205*dht22_temp)/0.01))/1000;
   
    //ppmv=mg/m3 * (0.08205*Tmp)/Molecular_mass
    //0.08205   = Universal gas constant in atm·m3/(kmol·K)
    ppmv=(((concentrationPM10*0.0283168/100) *  (0.08205*dht22_temp)/0.01))/1000;
    
    if ((ceil(concentrationPM10) != lastDUSTPM10)&&((long)concentrationPM10>0)) {
        lastDUSTPM10 = ceil(concentrationPM10);
    }
  
  /* END Code for DSM501 Dust Sensor reading */
  
  
  /*  BEGIN Code for DHT22 and BMP80 Sensor reading */
  
      dht22_temp = dht22.readTemperature();
      dht22_hum = dht22.readHumidity();
      bmp_180_temp = bmp.readTemperature();
      bmp.readPressure();
      bmp.readTemperature();
      bmp.readAltitude();
      bmp.readSealevelPressure();
      bmp_180_presure = bmp.readPressure();  
  
  /*  END Code for DHT22 and BMP80 Sensor reading */
  
  
  /*  BEGIN Code for outputing sensor data to external devices */
  
      // output sensor values to console in CSV format:
      // dht22_temp, bmp_180_temp, dht22_hum, bmp_180_presure, concentrationPM10, concentrationPM25, rpm, bucket_tips
     // Serial.print("\n");
    //  Serial.println("Temp (DHT), Temp (BMP), Humidity, Pressure, PM10, PM25");
     // Serial.print(dht22_temp);
      //Serial.print(",");
      //Serial.print(bmp_180_temp);
      //Serial.print(",");
      //Serial.print(dht22_hum);
      //Serial.print(",");
      //Serial.print(bmp_180_presure);
      //Serial.print(",");
      //Serial.print(concentrationPM10);
      //Serial.print(",");
      //Serial.println(concentrationPM25);

      output =   String(dht22_temp) + ',' + 
                 String(bmp_180_temp) + ',' + 
                 String(dht22_hum) + ',' + 
                 String(bmp_180_presure) + ',' + 
                 String(concentrationPM10) + ',' + 
                 String(concentrationPM25) + ',' + 
                 String(rpm) + ',' + 
                 String(bucket_tips) + ',' +
                 String("end_of_entry");
       
       Serial.println(output);
       send(output);
       
       //send(String(dht22_temp)+ ",");
     //  send(String(bmp_180_temp)+ ",");
      // send(String(dht22_hum)+ ",");
      // send(String(bmp_180_presure)+ ",");
     //  send(String(concentrationPM10)+ ",");
     //  send(String(concentrationPM25));
  /*  END Code for outputing sensor data to external devices */
 delay(1000);
}

// Get particulate matter concentration:
long getPM(int DUST_SENSOR_DIGITAL_PIN) {

  starttime = millis();

  while (1) {
        duration = pulseIn(DUST_SENSOR_DIGITAL_PIN, LOW);
    lowpulseoccupancy += duration;
    endtime = millis();
    
    if ((endtime-starttime) > sampletime_ms)
    {
    ratio = (lowpulseoccupancy-endtime+starttime)/(sampletime_ms*10.0);  // Integer percentage 0=>100
    if (lowpulseoccupancy==0){ // pulseIn(pin, low) returns 0 when no low value is detected 
      concentration = 0;
    }
    else {
      concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    }
    lowpulseoccupancy = 0;
    return(concentration);    
    }
  }  
}

void send(String message){  
  int msglen = message.length();
  // if the string to be sent is greater that 6 characters, 
  //    then divide it up and send the pieces one after the other 
  int ps = 3;  // Custom packet Size: length of string in chars per packet
  if (msglen > ps){
    // break the string into however many strings of 6 chars in length
    int submsgsAmount = ceil(msglen/ps);
    for (int i=0; i<submsgsAmount; i++){
      String my_message = (message.substring(i*ps, (i*ps)+ps));
      int message_length = my_message.length() + 1;
      char msg[message_length];
      my_message.toCharArray(msg, message_length);
      vw_send((uint8_t *)msg, message_length);
      delay(500);
      vw_wait_tx(); // Wait until the whole message is gone
     // Serial.print(msg);
    }
    Serial.print("\n");
  }
  else {
    String my_message = message;
    int message_length = my_message.length() + 1;
    char msg[message_length];
    my_message.toCharArray(msg, message_length);
    vw_send((uint8_t *)msg, message_length);
    vw_wait_tx(); // Wait until the whole message is gone
   }
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

void rainBucketTip(){
  bucket_tips++;
}

