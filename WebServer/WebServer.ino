#include "set.h"

void setup() {

  Serial.begin(115200);
  delay(5);
  Serial.println("");

  Serial.println("Start FS");
  FS_init(); 
  Serial.println("FileConfig");
  
  Settings_read();
  Settings_WiFi();
  Settings_Mqtt();
  
  Serial.println("Start WIFI");
  WIFIinit(); 
  Serial.println("Start Time");
  Time_init();
  Serial.println("Start WebServer");
  HTTP_init();
  Bmp280_init();
  Serial.println("Start OTA");
  OTA_init();
  MDNS.begin(host.c_str());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
  HTTP.handleClient();
  delay(1);
  client.loop();
  MQTT_loop();
  ArduinoOTA.handle();
}
