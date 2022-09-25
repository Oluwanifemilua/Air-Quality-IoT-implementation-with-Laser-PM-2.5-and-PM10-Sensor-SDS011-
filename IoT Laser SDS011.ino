

#include "ThingSpeak.h"
#include <WiFi.h>
char ssid[] = "MikkyTechie"; // your network SSID (name)
char pass[] = "16081994"; // your network password
int keyIndex = 0; // your network key Index number (needed only for WEP)
WiFiClient client;
 
unsigned long myChannelNumber = 851568; //update
const char * myWriteAPIKey = "SMTY1D11SZSJY74F"; //update
#include<Wire.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch

LiquidCrystal_I2C lcd (0x27, 16,2);
#include <SDS011.h>

float p10, p25;
int err;

SDS011 my_sds;

#ifdef ESP32
HardwareSerial port(2);
#endif

void setup(){
 my_sds.begin(&port);
 Serial.begin(115200);
 delay(10);
 WiFi.mode(WIFI_STA);
 ThingSpeak.begin(client); // Initialize ThingSpeak
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
 
 
 
 
 
 
 
 
 lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
  lcd.print("AIR QUALITY");
  lcd.setCursor(0,1);
lcd.print("MONITOR .....");
  delay(1000);
 
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }

  // scroll 16 positions (display length + string length) to the left
  // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);

}}

void loop(){
 err = my_sds.read(&p25, &p10);
 if (!err) {
    Serial.println("P2.5: " + String(p25));
    Serial.println("P10:  " + String(p10));
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PM2.5:");
  lcd.setCursor(6,0);
  lcd.print(p25);
  lcd.setCursor(11,0);
  lcd.print("ug/m3");
  lcd.setCursor(0,1);
  lcd.print("PM10 :");
  lcd.setCursor(6,1);
  lcd.print(p10);
  lcd.setCursor(11,1);
  lcd.print("ug/m3");
  }
  delay(100); 
 
 
 
 
 
 {  
                            
ThingSpeak.setField(1, p25);
ThingSpeak.setField(2, p10); 
    
 // write to the ThingSpeak channel
int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
if(x == 200){
Serial.println("Channel update successful.");
}
else{
Serial.println("Problem updating channel. HTTP error code " + String(x));
}
 
delay(20000); // Wait 20 seconds to update the channel again
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
}
