#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial gpsSerial(10, 11); // RX, TX
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        float lat = gps.location.lat();
        float lon = gps.location.lng();
        String url = "https://www.google.com/maps/search/?api=1&query=" + String(lat, 6) + "," + String(lon, 6);
        //Serial.print("Latitude: ");
        //Serial.println(lat, 6);
        //Serial.print("Longitude: ");
        //Serial.println(lon, 6);
        Serial.println(url);
      } else {
        Serial.println("GPS Location not available");
      }
      delay(1000);
    }
  }
}
