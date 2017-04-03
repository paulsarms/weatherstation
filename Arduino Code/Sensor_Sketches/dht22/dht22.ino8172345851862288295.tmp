/* How to use the DHT-22 sensor with Arduino uno
   Temperature and humidity sensor
   More info: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
   Dev: Michalis Vasilakis // Date: 1/7/2015 // www.ardumotive.com */

//Libraries
#include <DHT.h>;

//Constants
#define DHT22PIN 6     // what pin we're connected to
#define DHT_1_TYPE DHT22   // DHT 22  (AM2302)
DHT dht22(DHT22PIN, DHT_1_TYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup()
{
  Serial.begin(9600);
  dht22.begin();
}

void loop()
{
    delay(3000);
    //Read data and store it to variables hum and temp
    hum = dht22.readHumidity();
    temp= dht22.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("dht22 - Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
   
}

   
