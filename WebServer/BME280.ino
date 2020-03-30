#include <Wire.h>
#include <Adafruit_BME280.h>

float leavelPressur = 1013.25;

Adafruit_BME280 bme; // I2C

void Bmp280_init() {
    bme.begin(0x76);
}

void SendWeather() {
  jsonWrite(infoWeather, "Temperature", bme.readTemperature());
  jsonWrite(infoWeather, "Pressure", bme.readPressure() / 100.0F);
  jsonWrite(infoWeather, "Altitude", bme.readAltitude(leavelPressur));
  jsonWrite(infoWeather, "Humidity", bme.readHumidity());
}
