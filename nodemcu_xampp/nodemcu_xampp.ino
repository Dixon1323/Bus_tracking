#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

String URL = "http://169.254.59.22/sebin/post.php";
String receivedURL;
const char* ssid = "Iphone 12"; 
const char* password = "tubelight"; 
int temp = 50;
void setup()
 {
  Serial.begin(9600); // Set the baud rate to match the Arduino Mega
  connectWiFi();
 }

void loop() 
{
  if (Serial.available()) {
    String url = Serial.readString(); // Read the entire URL string from Arduino

    // Store the received URL in a variable
    receivedURL = url;
    String postData = "Location=" + receivedURL + "&speed=" + humidity; 
    Serial.println(postData);
    WiFiClient client;
    HTTPClient http;
  http.begin(client, URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.POST(postData); 
  String payload = http.getString(); 
  
  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(postData); 
  Serial.print("httpCode: "); Serial.println(httpCode); 
  Serial.print("payload : "); Serial.println(payload); 
  Serial.println("--------------------------------------------------");

    Serial.print("Received URL: ");
    Serial.println(receivedURL);
  }
}

void connectWiFi()
 {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}