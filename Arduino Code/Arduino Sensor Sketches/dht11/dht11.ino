#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h> 

dht DHT;
#define DHTTYPE DHT22

#define DHT11_PIN 7
void setup()
{
  Serial.begin(9600);
}
 
 
void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  String temp = "Temperature = ";
  String tempval = temp +DHT.temperature;
  String hum = "Humidity = ";
  String humval = hum +DHT.humidity;
  Serial.println(tempval);

  delay(1000);
}
