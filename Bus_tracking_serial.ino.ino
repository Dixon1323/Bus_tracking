#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D3,D8);
const char* ssid = "Redmi Note 10 Pro";
const char* password = "0987654321";
unsigned long previousMillis = 0;
unsigned long currentMillis;S
const long interval = 1000; 
String p1,p2,data,data1;
bool s1=false;
bool h1=false;

#define BOTtoken "5998333297:AAFUdtiTIaYJGZjaGzLNAYDBs45ChcwL8QE"

#define CHAT_ID "868712906"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);



void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(D2,OUTPUT);
  digitalWrite(D2,LOW);
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
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
      if (mySerial.available() > 0) 
       {
         data1 = mySerial.readStringUntil('\n');
         Serial.println(data1);
         bot.sendMessage(CHAT_ID,data1);
       }
  }

  data="";
  if (mySerial.available() > 0) {
    data = mySerial.readStringUntil('\n');
    Serial.println(data);
    dataread();
   // Serial.println(p1);
   // Serial.println(p2);
  }
}

void dataread()
{
  if(data=="14004B21F886")
  {
    digitalWrite(D2,HIGH);
    delay(200);
    digitalWrite(D2,LOW);
    delay(200);
    p1="Sebin Jaison";
    if(s1==false)
    {
      Serial.println("Enterrrrrrrrrrrrrrrrrrrrrrrrrred");
      bot.sendMessage(CHAT_ID, "Sebin has Entered");
      s1=!s1;
      
    }
    else
    {
      if(s1==true)
      {
        Serial.println("exxiiiiiiiiiiiiiiiiiiiit");
        bot.sendMessage(CHAT_ID, "Sebin has Exited");
        s1=!s1;
        
      }
    }

  }
  else
  if(data=="14004BE1B709")
  {
    digitalWrite(D2,HIGH);
    delay(200);
    digitalWrite(D2,LOW);
    delay(200);
    p2="Harikrishnan P J";
    if(h1==false)
    {
      Serial.println("Enterrrrrrrrrrrrrrrrrrrrrrrrrred");
      bot.sendMessage(CHAT_ID, "Hari has Entered");
      h1=!h1;
      
    }
    else
    {
      if(h1==true)
      {
        Serial.println("exxiiiiiiiiiiiiiiiiiiiit");
        bot.sendMessage(CHAT_ID, "Hari has Exited");
        h1=!h1;
        
      }
    }
  }
}
