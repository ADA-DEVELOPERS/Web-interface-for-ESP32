// ------------- Чтение значения json
String jsonRead(String &json, String name) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, json);
  return doc[name].as<String>();
}

// ------------- Чтение значения json
int jsonReadtoInt(String &json, String name) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, json);
  return doc[name];
}

// ------------- Запись значения json String
String jsonWrite(String &json, String name, String volume) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, json);
  doc[name] = volume;
  json = "";
  serializeJson(doc, json);
  return json;
}

// ------------- Запись значения json int
String jsonWrite(String &json, String name, int volume) {
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, json);
  doc[name] = volume;
  json = "";
  serializeJsonPretty(doc, json);
  return json;
}

// ------------- Чтение файла в строку
String readFile(String fileName, size_t len ) {
  File configFile = SPIFFS.open("/" + fileName, "r");
  if (!configFile) {
    return "Failed";
  }
  size_t size = configFile.size();
  if (size > len) {
    configFile.close();
    return "Large";
  }
  String temp = configFile.readString();
  configFile.close();
  return temp;
}

// ------------- Запись строки в файл
String writeFile(String fileName, String strings ) {
  File configFile = SPIFFS.open("/" + fileName, "w");
  if (!configFile) {
    return "Failed to open config file";
  }
  configFile.print(strings);
  //strings.printTo(configFile);
  configFile.close();
  return "Write sucsses";
}
