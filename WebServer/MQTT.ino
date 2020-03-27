int mqttConnect = 10000;

unsigned long timing;

// Принятие данных с MQTT
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void MQTT_loop() {
  if(wifiMode != "ap") {
    if(!client.connected() && millis() - timing > mqttConnect) {
      
      client.setServer(mqttServer.c_str(), mqttPort);
      client.setCallback(callback);
      Serial.println("Connecting to MQTT...");
      mqttStatus = "search";
      if (client.connect("ESP32Client", mqttUser.c_str(), mqttPassword.c_str())) {
        Serial.println("connected");
        Subscribe_mqtt();
        mqttStatus = "on";
      } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        timing = millis(); 
        mqttStatus = "off";
      }
    }
  }
}

void Subscribe_mqtt() {
  client.subscribe("esp/test");
}

void Publish_mqtt() {
  
  client.publish("esp/test", "ok");
}

