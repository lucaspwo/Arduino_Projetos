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

static uint32_t count = 0;
bool sender = false;
char go;
float array[3];
//bool ok = false;
void radioRecieve(void);

void setup(){
  dht.begin();
  pressure.begin();
  Serial.begin(9600);
  //printf_begin();
  radio.begin();
  radio.enableAckPayload();
  radio.setChannel(100);
  radio.setRetries(15,15);
  radio.setPayloadSize(16);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_16);
  //radio.openWritingPipe(pipe);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  attachInterrupt(0, radioRecieve, FALLING);
}

void loop(){
  
  /*if(isnan(h) || isnan(t)){
  } else {
  }
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
  
  delay(500);  // Pause for 2.5 seconds.*/
}

void radioRecieve(){
  Serial.println("1");
  Serial.print("sender = ");
  Serial.println(sender);
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  Serial.print("rx = ");
  Serial.println(rx);
  if(rx){
    if(sender == true){
      Serial.println("4");
      radio.read(&count, sizeof(count));
      func2();
      return;
    }
  //}
  if(sender == false){
    //if(rx){
      Serial.println("2");
      radio.read(&go, sizeof(char));
      radio.writeAckPayload(1, &count, sizeof(count));
      ++count;
      if(go == 'O'){
        func1();
        //delay(500);
      }
    }
  }
  Serial.println("Ops");
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

void func1(){
  sender = true;
  radio.stopListening();
  radio.openWritingPipe(pipe);
  readSensors();
  radio.write(&array, sizeof(array));
  Serial.println("3");
}

void func2(){
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  sender = false;
}