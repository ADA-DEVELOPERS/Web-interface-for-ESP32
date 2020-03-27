
void HTTP_init(void) {

  HTTP.on("/info.status.json", HTTP_GET, []() {
    SendWeather();
    String statCon = "{}";
    jsonWrite(statCon, "wifi", wifiStatus);
    jsonWrite(statCon, "mqtt", mqttStatus);
    jsonWrite(statCon, "home", "off");
    
    HTTP.send(200, "application/json", statCon);
  });

  HTTP.on("/info.conf.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", Config);
  });

  HTTP.on("/info.weather.json", HTTP_GET, []() {
    SendWeather();
    HTTP.send(200, "application/json", infoWeather);
  });

  HTTP.on("/settings.wifi.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", settingsWifi);
  });
  HTTP.on("/settings.upgrade.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", readFile("json/settings/Upgrade.json", 4096));
  });

  HTTP.on("/settings.network.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", settingsNetwork);
  });

  HTTP.on("/settings.mqtt.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", settingsMqtt);
  });

  HTTP.on("/settings.ap.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", settingsAP);
  });

  // --------------------Выдаем данные configJson
  HTTP.on("/config.live.json", HTTP_GET, []() {
    outData();
    HTTP.send(200, "application/json", configJson);
  });

  HTTP.on("/mqttsave", HTTP_GET, []() {
    String MqttSave = "{}";
    jsonWrite(MqttSave, "mqttServer", HTTP.arg("mqttServer"));
    jsonWrite(MqttSave, "mqttPort", HTTP.arg("mqttPort"));
    jsonWrite(MqttSave, "mqttUser", HTTP.arg("mqttUser"));
    jsonWrite(MqttSave, "mqttPassword", HTTP.arg("mqttPassword"));
    writeFile("json/settings/Mqtt.json", MqttSave);
    HTTP.send(200, "text / plain", "Save");
  });

  HTTP.on("/confsave", HTTP_GET, []() {
    String ConfSave = "{}";
    jsonWrite(ConfSave, "module", HTTP.arg("module"));
    jsonWrite(ConfSave, "name", HTTP.arg("name"));
    jsonWrite(ConfSave, "host", HTTP.arg("host"));
    writeFile("json/settings/Conf.json", ConfSave);
    HTTP.send(200, "text / plain", "Save");
  });

  HTTP.on("/wifisave", HTTP_GET, []() {
    String WifiSave = "{}";
    jsonWrite(WifiSave, "ssid", HTTP.arg("ssid"));
    jsonWrite(WifiSave, "password", HTTP.arg("password"));
    writeFile("json/settings/Wifi.json", WifiSave);
    HTTP.send(200, "text / plain", "Save");
  });

  HTTP.on("/apsave", HTTP_GET, []() {
    String ApSave = "{}";
    jsonWrite(ApSave, "ssidAP", HTTP.arg("ssidAP"));
    jsonWrite(ApSave, "passwordAP", HTTP.arg("passwordAP"));
    writeFile("json/settings/AP.json", ApSave);
    HTTP.send(200, "text / plain", "Save");
  });

  HTTP.on("/lansave", HTTP_GET, []() {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    JsonArray& apIP = root.createNestedArray("apIP");
    apIP.add(HTTP.arg("s1").toInt()); apIP.add(HTTP.arg("s2").toInt()); apIP.add(HTTP.arg("s3").toInt()); apIP.add(HTTP.arg("s4").toInt());
    JsonArray& gateway = root.createNestedArray("gateway");
    gateway.add(HTTP.arg("r1").toInt()); gateway.add(HTTP.arg("r2").toInt()); gateway.add(HTTP.arg("r3").toInt()); gateway.add(HTTP.arg("r4").toInt());
    JsonArray& NMask = root.createNestedArray("NMask");
    NMask.add(HTTP.arg("m1").toInt()); NMask.add(HTTP.arg("m2").toInt()); NMask.add(HTTP.arg("m3").toInt()); NMask.add(HTTP.arg("m4").toInt());
    JsonArray& primaryDNS = root.createNestedArray("primaryDNS");
    primaryDNS.add(HTTP.arg("f1").toInt()); primaryDNS.add(HTTP.arg("f2").toInt()); primaryDNS.add(HTTP.arg("f3").toInt()); primaryDNS.add(HTTP.arg("f4").toInt()); 
    JsonArray& secondaryDNS = root.createNestedArray("secondaryDNS");
    secondaryDNS.add(HTTP.arg("d1").toInt()); secondaryDNS.add(HTTP.arg("d2").toInt()); secondaryDNS.add(HTTP.arg("d3").toInt()); secondaryDNS.add(HTTP.arg("d4").toInt());
    root.prettyPrintTo(Serial);
    File configFile = SPIFFS.open("/json/settings/Network.json", "w");
    if (!configFile) {
      HTTP.send(200, "text / plain", "NotSave");
    }
    String str = "";
    root.printTo(str);
    configFile.print(str);
    configFile.close();
    HTTP.send(200, "text / plain", "Save");
  });
  
  // -------------------Выдаем данные configSetup
  HTTP.on("/restart", HTTP_GET, []() {
    String restart = HTTP.arg("device");          // Получаем значение device из запроса
    if (restart == "ok") {                         // Если значение равно Ок
      HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
      delay(2000);
      ESP.restart();                                // перезагружаем модуль
    }
    else {                                        // иначе
      HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
    }
  });

  // Запускаем HTTP сервер
  HTTP.begin();
}
