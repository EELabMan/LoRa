#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 8
#define rst 1
#define dio0 2

void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  //LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe/Africa
  //915E6 for North America
  if(!LoRa.begin(915E6)) {
    Serial.println(".");
    while (1);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  

/*The spreading factor used by the radio (try setting to a higher value to increase 
the receiver’s ability to distinguish signal from noise or to a lower value to 
increase the data transmission rate). Valid values are limited to 6, 7, 8, 9, 10, 11, or 12.*/
LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs https://github.com/sandeepmistry/arduino-LoRa/tree/master
//https://docs.circuitpython.org/projects/rfm9x/en/latest/api.html
}

void loop() 
{

  String LoRaData; 
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available())
    {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    
   }
}