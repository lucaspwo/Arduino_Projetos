/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * You need to install this for ESP8266 development:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define red 12
#define gre 14
#define blu 04

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0ab851d981ad498cb0dd446197b2592f";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "BonoNet";
char pass[] = "bonooliveira402";

int l_red, l_gre, l_blu;
int fade;
int interval;

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop(){
  Blynk.run();
}

BLYNK_WRITE(V4){
  l_blu = param.asInt();
}

BLYNK_WRITE(V3){
  l_gre = param.asInt();
}

BLYNK_WRITE(V2){
  l_red = param.asInt();
}

BLYNK_WRITE(V1){
  interval = param.asInt();
}

BLYNK_WRITE(V0){
  fade = param.asInt();

  while(fade == 0){
    analogWrite(red, l_red);
    analogWrite(gre, l_gre);
    analogWrite(blu, l_blu);
    fade = param.asInt();
  }
  while(fade == 1){
    for(int i = 0; i < 1024; i++){
      analogWrite(red, i);
      analogWrite(gre, i);
      analogWrite(blu, i);
      delay(interval);
    }
    for(int i = 1023; i >= 0; i--){
      analogWrite(red, i);
      analogWrite(gre, i);
      analogWrite(blu, i);
      delay(interval);
    }
    fade = param.asInt();
  }
}
