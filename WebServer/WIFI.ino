

void WIFIinit() {
  // Попытка подключения к точке доступа
  DynamicJsonDocument root(1024);
  DeserializationError error = deserializeJson(root, settingsNetwork);
  int apiIp[4] = {0,0,0,0};
  int getIp[4] = {0,0,0,0};
  int masIp[4] = {0,0,0,0};
  int priIp[4] = {0,0,0,0};
  int secIp[4] = {0,0,0,0};
  
  apiIp[0] = root["apIP"][0];           apiIp[1] = root["apIP"][1];          apiIp[2] = root["apIP"][2];          apiIp[3] = root["apIP"][3];
  getIp[0] = root["gateway"][0];        getIp[1] = root["gateway"][1];       getIp[2] = root["gateway"][2];       getIp[3] = root["gateway"][3];
  masIp[0] = root["NMask"][0];          masIp[1] = root["NMask"][1];         masIp[2] = root["NMask"][2];         masIp[3] = root["NMask"][3];
  priIp[0] = root["primaryDNS"][0];     priIp[1] = root["primaryDNS"][1];    priIp[2] = root["primaryDNS"][2];    priIp[3] = root["primaryDNS"][3];
  secIp[0] = root["secondaryDNS"][0];   secIp[1] = root["secondaryDNS"][1];  secIp[2] = root["secondaryDNS"][2];  secIp[3] = root["secondaryDNS"][3];

  
  IPAddress apIP(apiIp[0], apiIp[1], apiIp[2], apiIp[3]);
  IPAddress gateway(getIp[0], getIp[1], getIp[2], getIp[3]); // IP роутера
  IPAddress NMask(masIp[0], masIp[1], masIp[2], masIp[3]);
  IPAddress primaryDNS(priIp[0], priIp[1], priIp[2], priIp[3]); //optional
  IPAddress secondaryDNS(secIp[0], secIp[1], secIp[2], secIp[3]); //optional

  
  WiFi.config(apIP, gateway, NMask, primaryDNS, secondaryDNS);  // Конфигурация статического IP на роутере
  WiFi.mode(WIFI_STA);
  byte tries = 11;
  WiFi.begin(_ssid.c_str(), _password.c_str());
  // Делаем проверку подключения до тех пор пока счетчик tries
  // не станет равен нулю или не получим подключение
  wifiStatus = "off";
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    // Если не удалось подключиться запускаем в режиме AP
    Serial.println("");
    Serial.println("WiFi up AP");
    WiFi.disconnect();
    WiFi.softAPConfig(apIP, apIP, NMask);     // Конфигурация статического IP AP
    WiFi.mode(WIFI_STA);
    delay(1000);
    WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    wifiStatus = "on";
    wifiMode = "ap";

    
  } else {
    // Иначе удалось подключиться отправляем сообщение
    // о подключении и выводим адрес IP
    Serial.println("");
    Serial.println("WiFi connected to Delink");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    wifiStatus = "on";
    wifiMode = "wifi";
  }
}
