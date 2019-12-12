
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const int motorPin = 6;
const int HeatingPad = 3;
RF24 radio(9, 8);  // CE, CSN

const byte address[6] = "0001A";

float t = 0;
/*
 * What we must do first is to receive the code that the transmitter is sending us. 
 */
void setup()
{
  while (!Serial);
  Serial.begin(9600);

  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(125);
  radio.openReadingPipe(0, address);
  radio.startListening();

  pinMode(motorPin, OUTPUT);
  pinMode(HeatingPad, OUTPUT);
}

void loop()
{
  if (radio.available())
  {
    radio.read(&t, sizeof(t));
    Serial.println(t);
    /*
     * Here we receive the variable that the transmitter sent us. In this case is ''t'' that means Temperature. 
     * We print the variable to make comprovations.
     */
  }
  if (t <= 20) {
    analogWrite(motorPin, 50);
        analogWrite(HeatingPad, 0);
   // digitalWrite(HeatingPad, LOW);

    //Serial.println("M On, H Off");
/*
 * When Temperature ''t'' is lower than 20, the Vibration Motor activates. We're using Analogic Pins to define the Power to it and get a better control in this.
 */
  }
  else if ( t >= 25) {

    analogWrite(HeatingPad, 255);
    //Serial.println("M Off, H Off");

/*
 * On the other hand if temperature is higher than 25, the HeatingPad activates and gets hot. We use Analogic Pin for the same reason as the motor.
 */

  }
  else {
    analogWrite(HeatingPad, 0);
        analogWrite(motorPin, 0);
  //  digitalWrite(motorPin, HIGH);
/*
 * Also, if the Temperature is between 20 and 25, nothings happens. It is better in this case to get off all the devices so it does not makes interference.
 */
    //Serial.println("M Off, H On");
  }
}
