int mqttConnect = 10000;
int mqttPublish = 15000;

unsigned long timingConnect;
unsigned long timingPublish;

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
    if(!client.connected() && millis() - timingConnect > mqttConnect) {
      client.setServer(mqttServer.c_str(), mqttPort);
      client.setCallback(callback);
      Serial.println("Connecting to MQTT...");
      mqttStatus = "search";
      if (client.connect(host.c_str(), mqttUser.c_str(), mqttPassword.c_str())) {
        Serial.println("connected");
        Subscribe_mqtt();
        mqttStatus = "on";
      } else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        timingConnect = millis();
        mqttStatus = "off";
      }
    }
  }
}

void Subscribe_mqtt() {
  String subServerMqtt = nameMod + "/" + host + "/set";
  client.subscribe(subServerMqtt.c_str());
}

void Publish_mqtt() {
  if(millis() - timingPublish > mqttPublish) {
    timingPublish = millis();
    SendWeather();
    String topicTeperature = nameMod + "/" + host + "/Temperature";
    String topicPressure =   nameMod + "/" + host + "/Pressure";
    String topicAltitude =   nameMod + "/" + host + "/Altitude";
    String topicHumidity =   nameMod + "/" + host + "/Humidity";
    client.publish(topicTeperature.c_str(), jsonRead(infoWeather, "Temperature").c_str());
    client.publish(topicPressure.c_str(), jsonRead(infoWeather, "Pressure").c_str());
    client.publish(topicAltitude.c_str(), jsonRead(infoWeather, "Altitude").c_str());
    client.publish(topicHumidity.c_str(), jsonRead(infoWeather, "Humidity").c_str());
  }
}
