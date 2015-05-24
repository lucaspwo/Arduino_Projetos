#include <SPI.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include <DHT.h>
#include "RF24.h"
#include "nRF24L01.h"

SFE_BMP180 pressure;
RF24 radio(9,10);

#define ALTITUDE 34.4
#define DHTPIN 3
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const uint64_t pipe = 0xF0F0F0F0E1LL;

char go;
float array[3];
void radioRecieve(void);

void setup(){
  dht.begin();
  pressure.begin();
  Serial.begin(57600);
  radio.begin();
  radio.enableAckPayload();
  radio.setChannel(100);
  radio.setRetries(15,15);
  radio.setPayloadSize(16);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  attachInterrupt(0, radioRecieve, FALLING);
}

void loop(){
}

void radioRecieve(){
  //Serial.println("1");
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  //Serial.print("rx = ");
  //Serial.println(rx);
  if(rx){
      //Serial.println("2");
      radio.read(&go, sizeof(char));
      readSensors();
      /*array[0] = 30.0;
      array[1] = 81.7;
      array[2] = 77.0;
      delay(500);*/
      radio.writeAckPayload(1, &array, sizeof(array));
  }
  //Serial.println("Fim");
}

void readSensors(){
  char status;
  double T,P,p0,a;
  float h = dht.readHumidity();
  array[2] = h;
  float t = dht.readTemperature();
  float temp = (9.0/5.0)*t+32.0;
  array[1] = temp;
  status = pressure.startTemperature();
  if (status != 0){
    // Wait for the measurement to complete:
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0){

      status = pressure.startPressure(3);
      if (status != 0){
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(P,T);
        if (status != 0){
          // Print out the measurement:
          p0 = pressure.sealevel(P,ALTITUDE);
          float pres = p0*0.0295333727;
          array[0] = pres;

          Serial.print("Press = ");
          Serial.print(array[0]);
          Serial.print("\t");
          Serial.print("Temp = ");
          Serial.print(array[1]);
          Serial.print("\t");
          Serial.print("Hum = ");
          Serial.println(array[2]);
        }
      }
    }
  }
}
