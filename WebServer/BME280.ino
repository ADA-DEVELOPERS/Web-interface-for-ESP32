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

void printValues() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(leavelPressur));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}
