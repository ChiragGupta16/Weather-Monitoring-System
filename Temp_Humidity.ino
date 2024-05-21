

#include<WiFi.h>
#include "DHTesp.h"
#include "ThingSpeak.h"


const byte DhtPin = 26;
const char* API = "PWM01PYVWAMLA72T";
const int channel = 2405378;
const char* WIFI_NAME = "vivo";
const char* WIFI_PASSWORD = "";
const char* server = "api.thingspeak.com";


DHTesp sensor;
WiFiClient client;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  sensor.setup(DhtPin,DHTesp::DHT11);
  
  WiFi.begin(WIFI_NAME,WIFI_PASSWORD);
  
  Serial.println("WiFi Connected");
  Serial.println("Local Host : "+ String(WiFi.localIP()));
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() {
  TempAndHumidity data = sensor.getTempAndHumidity();
  ThingSpeak.setField(1,data.temperature);
  ThingSpeak.setField(2,data.humidity);
 
  
  int x = ThingSpeak.writeFields(channel,API);
  
  
   Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  
  if(x==200)
  {
    Serial.println("Data Push Successfull");
  }
  else
  {
     Serial.println("Data push Failed");
     }


     delay(9000);
}
