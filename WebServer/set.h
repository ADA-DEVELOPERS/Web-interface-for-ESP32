#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>            
#include <ArduinoOTA.h>         // Прошивка по WIFI
#include <FS.h>                 // Библиотека для работы с файловой системой esp32
#include "SPIFFS.h"             // Библиотека для работы с файловой системой esp32
#include <ArduinoJson.h>        // Установить из менеджера библиотек. https://arduinojson.org/
#include <PubSubClient.h>       // Библиотека для работы MQTT


WiFiClient espClient;
PubSubClient client(espClient);

WebServer HTTP(80);
//int ip[4] = {0,0,0,0};

String mqttStatus = "off";
String wifiStatus = "disconnect";
String wifiMode = "no";

//Settings_Network();



//IPAddress apIP(ip[0], ip[1], ip[2], ip[3]);
//IPAddress gateway(192, 168, 1, 1); // IP роутера
//IPAddress NMask(255, 255, 255, 0);
//IPAddress primaryDNS(8, 8, 8, 8); //optional
//IPAddress secondaryDNS(8, 8, 4, 4); //optional

//Для файловой системы
File fsUploadFile;
IPAddress apIP(0, 0, 0, 0);
String infoWeather = "{}";
String settingsWifi = "{}";
String settingsMqtt = "{}";
String settingsAP = "{}";
String settingsNetwork = "{}";
String Config = "{}";

// Определяем переменные wifi
String _ssid     = ""; // Для хранения SSID
String _password = ""; // Для хранения пароля сети
String _ssidAP = "";   // SSID AP точки доступа
String _passwordAP = ""; // пароль точки доступа
String nameMod = "";
String idMod = "";
String host = "";

int timezone = 6;               // часовой пояс GTM

String mqttServer = "";
int mqttPort = 0;
String mqttUser = "";
String mqttPassword = "";


String configJson = "{}";
String timerJson = "{}";
String analogJson = "{}";



