/* How to use the DHT-22 sensor with Arduino uno
   Temperature and humidity sensor
   More info: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
   Dev: Michalis Vasilakis // Date: 1/7/2015 // www.ardumotive.com 

--For the BMP180 Sensor--
// Connect VCC of the BMP180 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
*/

//Libraries
#include <DHT.h>;
#include <Wire.h>
#include <Adafruit_BMP085.h>

//Constants
#define DHT22PIN 6     // what pin we're connected to
#define DHT_1_TYPE DHT22   // DHT 22  (AM2302)
DHT dht22(DHT22PIN, DHT_1_TYPE); //// Initialize DHT sensor for normal 16mhz Arduino
Adafruit_BMP085 bmp;

//Variables
int chk;
float  dht22_hum;  //Stores dht22 humidity value
float dht22_temp; //Stores dht22 temperature value
float bmp_180_temp; //Stores bmp180 temperature value
float bmp_180_presure; //Stores bmp180 pressure value
const int hallPin = 12; 
int hallState = 0; 
int prev_hallState = 0;
int t, cur_t; //time variables

void setup()
{
  Serial.begin(9600);
  dht22.begin();
  bmp.begin();
  // initialize the hall effect sensor pin as an input:
  pinMode(hallPin, INPUT); 
}

void loop()
{

    //Read data and store it to variables hum and temp
    dht22_temp = dht22.readTemperature();
    dht22_hum = dht22.readHumidity();
    bmp_180_temp = bmp.readTemperature();
    bmp.readPressure();
    bmp.readTemperature();
    bmp.readAltitude();
    bmp.readSealevelPressure();
    bmp_180_presure = bmp.readPressure();  
   //  output sensor values to console in CSV format:
    // dht22_temp, bmp_180_temp, dht22_hum, bmp_180_presure
    Serial.print(dht22_temp);
   Serial.print(",");
    Serial.print(bmp_180_temp);
    Serial.print(",");
    Serial.print(dht22_hum);
    Serial.print(",");
    Serial.println(bmp.readPressure());
    delay(60000);

}

   
