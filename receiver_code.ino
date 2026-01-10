#include <SPI.h>
#include <LoRa.h>
import serial 

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    Serial.println("");
    Serial.println("..............");
    Serial.println("Received packet");

    while (LoRa.available()) {
      char incoming = (char)LoRa.read();

      if (incoming == 'c') {
        Serial.println("Error");
      } else if (incoming == '\n') {
        // End of line, indicating the end of a sensor reading
        Serial.println();
      } else {
        Serial.print(incoming);
        incoming.flushInput();
      }
    }

    delay(1000);  // Adjust delay based on the sender's transmission interval
  }
}
