#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
float lat,lon;
const char* ssid = "Redmi Note 10 Pro";
const char* password = "0987654321";
unsigned long previousMillis = 0,currentMillis;
const long interval = 10000;

#define BOTtoken "5998333297:AAFUdtiTIaYJGZjaGzLNAYDBs45ChcwL8QE"

#define CHAT_ID "868712906"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);



void setup() {
  currentMillis = millis();
  Serial.begin(9600);
  configTime(0, 0, "pool.ntp.org"); 
  client.setTrustAnchors(&cert);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "Wifi Connected");
}

void loop()
{
  if (currentMillis - previousMillis >= interval)
   {
    previousMillis = currentMillis;
    sendloc();
  }


}


void sendloc()
{
while (Serial.available() > 0) 
  {
    if (gps.encode(Serial.read()))
     {
      if (gps.location.isValid())
       {
        lat = gps.location.lat();
        lon = gps.location.lng();
        String url = "https://www.google.com/maps/search/?api=1&query=" + String(lat, 6) + "," + String(lon, 6);
        //Serial.print("Latitude: ");
        //Serial.println(lat, 6);
        //Serial.print("Longitude: ");
        //Serial.println(lon, 6);
        Serial.println(url);
        bot.sendMessage(CHAT_ID, url);
      } else {
        bot.sendMessage(CHAT_ID,s"GPS Location not available");
        //Serial.println("GPS Location not available");
      }
}
}
}
