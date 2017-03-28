/*
 * taken from:
 * http://www.buildcircuit.com/how-to-use-rf-module-with-arduino/
 * 
  SimpleReceive
  This sketch displays text strings received using VirtualWire
  Connect the Receiver data pin to Arduino pin 11
*/
#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
String fullData;
int i;
String strData;
void setup()
{
  Serial.begin(9600);
  Serial.println("Device is ready");
  vw_set_ptt_inverted(true); // Required for DR3100
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  vw_rx_start(); // Start the receiver
 
 
}
void loop()
{
  
  if(vw_wait_rx_max(7000)){
    if (vw_get_message(message, &messageLength)) // Non-blocking
      {
        strData="";
        for (char c : message) {
          strData += (String)c;
        }
        //String str(strData);
        Serial.print(strData);
      }
  }
  else {
    Serial.println();
  }
}




