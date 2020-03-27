void Settings_read() {
  settingsWifi = readFile("json/settings/Wifi.json", 4096);
  settingsNetwork = readFile("json/settings/Network.json", 4096);
  settingsMqtt = readFile("json/settings/Mqtt.json", 4096);
  settingsAP = readFile("json/settings/AP.json", 4096);
  Config = readFile("json/settings/Conf.json", 4096);
  Serial.print("Settings Read Done");
}

void Settings_WiFi() {
  
  _ssid =         jsonRead(settingsWifi, "ssid");
  _password =     jsonRead(settingsWifi, "password");
  _ssidAP =       jsonRead(settingsAP, "ssidAP");
  _passwordAP =   jsonRead(settingsAP, "passwordAP");
  
  nameMod =       jsonRead(Config, "module");
  idMod =         jsonRead(Config, "name");
  host =          jsonRead(Config, "host");
  Serial.print("Settings WiFi Done >>>>>>");
}
 
void Settings_Mqtt() {
  String s = "";
  int n = 0;


  host = jsonRead(settingsWifi, "host");
  mqttServer = jsonRead(settingsMqtt, "mqttServer");
  mqttPort = jsonReadtoInt(settingsMqtt, "mqttPort");
  mqttUser = jsonRead(settingsMqtt, "mqttUser");
  mqttPassword = jsonRead(settingsMqtt, "mqttPassword");
}
