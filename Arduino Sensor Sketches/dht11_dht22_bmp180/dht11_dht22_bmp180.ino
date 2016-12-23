/* How to use the DHT-22 sensor with Arduino uno
   Temperature and humidity sensor
   More info: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
   Dev: Michalis Vasilakis // Date: 1/7/2015 // www.ardumotive.com */

//Libraries
#include <DHT.h>;
#include <Adafruit_BMP085.h>
#include <Wire.h>

//Constants
#define DHT22PIN 6     // what pin we're connected to
#define DHT_1_TYPE DHT22   // DHT 22  (AM2302)
DHT dht22(DHT22PIN, DHT_1_TYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define DHT11PIN 7     // what pin we're connected to
#define DHT_2_TYPE DHT11   // DHT 22  (AM2302)
DHT dht11(DHT11PIN, DHT_2_TYPE); //// Initialize DHT sensor for normal 16mhz Arduino
Adafruit_BMP085 bmp;

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
int pres; //Stores pressure value

void setup()
{
  Serial.begin(9600);
  dht22.begin();
  dht11.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}

void loop()
{
    delay(3000);
    //Read data and store it to variables hum and temp

    //DHT22 - Print temp and humidity values to serial monitor
    hum = dht22.readHumidity();
    temp= dht22.readTemperature();
    Serial.print("dht22 - Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");

    //DHT11 Print temp and humidity values to serial monitor
    hum = dht11.readHumidity();
    temp= dht11.readTemperature();
    Serial.print("dht11 - Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");

    //BMP180 - Print temp and humidity values to serial monitor
    pres = bmp.readPressure();
    temp= bmp.readTemperature();
    Serial.print("bmp180 - Pressure: ");
    Serial.print(pres);
    Serial.print("pa , Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
}

   
