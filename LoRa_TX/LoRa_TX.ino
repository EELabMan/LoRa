#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#define DHTPIN 4                                                           // what digital pin we're connected to
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  
  dht.begin();     //initialise DHT11

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0xF3);
  LoRa.setTxPower(20);

//property spreading_factor: Literal[6, 7, 8, 9, 10, 11, 12]¶

/*The spreading factor used by the radio (try setting to a higher value to increase 
the receiver’s ability to distinguish signal from noise or to a lower value to 
increase the data transmission rate). Valid values are limited to 6, 7, 8, 9, 10, 11, or 12.*/
LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs https://github.com/sandeepmistry/arduino-LoRa/tree/master
// https://docs.circuitpython.org/projects/rfm9x/en/latest/api.html

}

void loop() 
{
  float h = dht.readHumidity();                                              
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {                                                
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print("Sending packet: ");
  Serial.println(counter);
  // send packet
  LoRa.beginPacket();
  LoRa.print("ADD YOUR NAME HERE !!!   Data:");
  LoRa.print(counter);
  LoRa.print("> ");
  LoRa.print("Temperature: ");
  LoRa.print(t);
  LoRa.print(" ");
  LoRa.print("humidity");
  LoRa.print(h);
  LoRa.endPacket();

  counter++;

  delay(5000);
}