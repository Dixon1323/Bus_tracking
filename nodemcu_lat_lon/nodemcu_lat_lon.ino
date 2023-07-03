void setup() {
  Serial.begin(115200); // Set the baud rate to match the Arduino Mega
}

void loop() {
  if (Serial.available()) {
    String url = Serial.readStringUntil('\n'); // Read the URL string from Arduino

    // Find the index of the latitude and longitude values in the URL
    int latStartIndex = url.indexOf("query=") + 6;
    int latEndIndex = url.indexOf(",", latStartIndex);
    int lonStartIndex = latEndIndex + 1;
    int lonEndIndex = url.indexOf("\"", lonStartIndex);

    // Extract the latitude and longitude values
    String latitude = url.substring(latStartIndex, latEndIndex);
    String longitude = url.substring(lonStartIndex, lonEndIndex);

    // Print the extracted values
    Serial.print("Latitude: ");
    Serial.println(latitude);
    Serial.print("Longitude: ");
    Serial.println(longitude);
  }
}
