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

const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

float array[3];
bool ok = false;
//void radioRecieve(void);

void setup(){
  dht.begin();
  pressure.begin();
  //Serial.begin(57600);
  radio.begin();
  radio.setChannel(100);
  radio.setRetries(15,15);
  radio.setPayloadSize(16);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  //attachInterrupt(0, radioRecieve, FALLING);
}

void loop(){
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
      //Serial.print("Temp = ");
      //Serial.print((9.0/5.0)*T+32.0,2);
      //Serial.print("\t");

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
        }
      }
    }
  }

  if(isnan(h) || isnan(t)){
    //nada
  } else {
    //nada
  }
  /*Serial.print("Press = ");
  Serial.print(array[0]);
  Serial.print("\t");
  Serial.print("Temp = ");
  Serial.print(array[1]);
  Serial.print("\t");
  Serial.print("Hum = ");
  Serial.println(array[2]);
  Serial.print("Enviando...");*/
  radio.stopListening();
  
  ok = radio.write(&array, sizeof(array));
  if(ok == true){
    //Serial.println(" Ok!");
  }
  else{
    //Serial.println(" Falhou.");
  }
  radio.startListening();
  
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  while (!radio.available() && !timeout)
    if (millis() - started_waiting_at > 200 )
      timeout = true;
      
  if (timeout){
    //Serial.println("Demorou para responder.");
  }
  else{
    //Serial.println("Sucesso no retorno!");
    char chegou;
    radio.read(&chegou, sizeof(char));
  }
  
  delay(500);  // Pause for 2.5 seconds.
}

/*void radioRecieve(){
}*/
