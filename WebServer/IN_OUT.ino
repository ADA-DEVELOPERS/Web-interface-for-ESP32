// поместим данные для web страницы в json строку configJson
// Будем вызывать эту функцию каждый раз при запросе /config.live.json
// jsonWrite(строка, "ключ", значение_число); Так можно дабавить или обнавить json значение ключа в строке
// jsonWrite(строка, "ключ", "значение_текст");
void outData() {
  jsonWrite(configJson, "time", GetTime());
  jsonWrite(configJson, "date", GetDate());
  jsonWrite(configJson, "gpio0", digitalRead(0));
  jsonWrite(configJson, "A0", analogRead(A0));
  uint32_t chipid = ESP.getEfuseMac();
  jsonWrite(configJson, "flashChip", String(chipid));
}

void GRAF_init() {
  HTTP.on("/analog.json", HTTP_GET, []() {
    String data = graf(5, 10, 20);
    jsonWrite(data, "points", 20);
    jsonWrite(data, "refresh", 4000);
    HTTP.send(200, "application/json", data);
  });
}