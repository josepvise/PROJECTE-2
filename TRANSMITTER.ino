
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
RF24 radio(9, 8);

const byte address[6] = "0001A";

/* What we basically do in this code is to program the Transmitter device. It sends the temperature to the receiver.
 *  We changed the channel where it sends the information to get a more fluence program. 
 *  Also what we have to program is the address which connects with the other device, in our case ''0001A''.
 *  Using the code radio.write we send the variable to the other wireless module.
 */

void setup()
{
  //Serial.begin(9600);
  dht.begin();

  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(125);
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop()
{
  float t = dht.readTemperature();
  radio.write(&t, sizeof(t));
  //Serial.println(t);
  delay(500);
}
