
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
    String MqttSave = "";
    jsonWrite(MqttSave, "mqttServer", HTTP.arg("mqttServer"));
    Serial.println(MqttSave);
    jsonWrite(MqttSave, "mqttPort", HTTP.arg("mqttPort"));
    jsonWrite(MqttSave, "mqttUser", HTTP.arg("mqttUser"));
    jsonWrite(MqttSave, "mqttPassword", HTTP.arg("mqttPassword"));
    Serial.println(MqttSave);
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
    DynamicJsonDocument doc(1024);
    doc["apIP"] = serialized("["+ HTTP.arg("s1")  +","+  HTTP.arg("s2").toInt()  +","+ HTTP.arg("s3")  +","+ HTTP.arg("s4")  +"]");
    doc["gateway"] = serialized("["+ HTTP.arg("r1")  +","+  HTTP.arg("r2")  +","+ HTTP.arg("r3")  +","+ HTTP.arg("r4")  +"]");
    doc["NMask"] = serialized("["+ HTTP.arg("m1")  +","+  HTTP.arg("m2")  +","+ HTTP.arg("m3")  +","+ HTTP.arg("m4")  +"]");
    doc["primaryDNS"] = serialized("["+ HTTP.arg("f1")  +","+  HTTP.arg("f2")  +","+ HTTP.arg("f3")  +","+ HTTP.arg("f4")  +"]");
    doc["secondaryDNS"] = serialized("["+ HTTP.arg("d1")  +","+  HTTP.arg("d2")  +","+ HTTP.arg("d3")  +","+ HTTP.arg("d4")  +"]");
    File configFile = SPIFFS.open("/json/settings/Network.json", "w");
    if (!configFile) {
      HTTP.send(200, "text / plain", "NotSave");
    }
    String json = "";
    serializeJsonPretty(doc, json);
    configFile.print(json);
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

  HTTP.onNotFound([]() {
    if (!handleFileRead(HTTP.uri())){
      String file404 = "404.html";
      String contentType = getContentType(file404);
      if (SPIFFS.exists(file404)) {
          File file = SPIFFS.open("/" + file404, "r");
          size_t sent = HTTP.streamFile(file, contentType);
          file.close();
      } else {
        HTTP.send(404, "text/plain", "FileNotFound");
      }
    }
  });

  // Запускаем HTTP сервер
  HTTP.begin();
}
