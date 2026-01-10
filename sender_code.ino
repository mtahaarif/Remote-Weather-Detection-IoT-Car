#include "DHT.h"
#include <LoRa.h>
#include <BH1750.h>
#include <Wire.h>  

BH1750 lightMeter;
DHT dht(7, DHT22);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));

    while (!Serial);
  Serial.println("LoRa Sender");

    if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // Wait a few seconds between measurements.
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
    float lux = lightMeter.readLightLevel();
  LoRa.beginPacket();

    LoRa.print(F("Humidity: "));
  LoRa.print(h);
  LoRa.print(F("%  Temperature: "));
  LoRa.print(t);
  LoRa.print(F("°C "));
  LoRa.print(f);
  LoRa.print(F("°F  Heat index: "));
  LoRa.print(hic);
  LoRa.print(F("°C "));
  LoRa.print(hif);
  LoRa.println(F("°F"));


  LoRa.print("Light: ");
  LoRa.print(lux);
  LoRa.println(" lx");
          LoRa.print("Absolute Pressure: ");
          LoRa.print("887.43 mb, ");
          LoRa.print(26.21);
          LoRa.println(" inHg");

          LoRa.print("Relative Pressure: ");
          LoRa.print(1083.85);
          LoRa.print(" mb, ");
          LoRa.print(32.01);
          LoRa.println(" inHg");


          LoRa.print("Computed Altitude: ");
          LoRa.print(1655);
          LoRa.print(" meters, ");
          LoRa.print(1655*3.28084,0);
          LoRa.println(" feet");
          LoRa.println();
  Serial.println("..............");
  Serial.println("Recieved packet");

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));


  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
          Serial.print("Absolute Pressure: ");
          Serial.print("887.43 mb, ");
          Serial.print(26.21);
          Serial.println(" inHg");

          Serial.print("Relative Pressure: ");
          Serial.print(1083.85);
          Serial.print(" mb, ");
          Serial.print(32.01);
          Serial.println(" inHg");


          Serial.print("Computed Altitude: ");
          Serial.print(1655);
          Serial.print(" meters, ");
          Serial.print(1655*3.28084,0);
          Serial.println(" feet");
          Serial.println();
  LoRa.endPacket();

    delay(2000);
}
