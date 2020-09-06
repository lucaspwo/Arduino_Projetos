#include <TM1637Display.h>
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS3232RTC.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define LED_PIN 1
#define LED_COUNT 1

#define CLK 3
#define DIO 4

Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

TM1637Display display(CLK, DIO);

uint8_t tempo[] = {0xff, 0xff, 0xff, 0xff};

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  led.begin();
  led.show();
  led.setBrightness(65);
  
  setSyncProvider(RTC.get);

  display.setBrightness(0x0f);
  display.setSegments(tempo);
}

void loop() {
  static time_t tLast;
  time_t t;
  
  t = now();
  if (t != tLast) {
    tLast = t;
    if(second(t) % 2){
      mostraHora(t, true);
    } else{
      mostraHora(t, false);
    }
    switch (weekday(t)){
      case 1:
        led.setPixelColor(0, led.Color(255,   255,   255));
        led.show();
        break;
      case 2:
        led.setPixelColor(0, led.Color(255,   0,   0));
        led.show();
        break;
      case 3:
        led.setPixelColor(0, led.Color(255,   255,   0));
        led.show();
        break;
      case 4:
        led.setPixelColor(0, led.Color(0,   0,   255));
        led.show();
        break;
      case 5:
        led.setPixelColor(0, led.Color(0,   255,   255));
        led.show();
        break;
      case 6:
        led.setPixelColor(0, led.Color(255,   0,   255));
        led.show();
        break;
      case 7:
        led.setPixelColor(0, led.Color(0,   255,   0));
        led.show();
        break;
    }
  }
}

void mostraHora(time_t t, bool seg){
  if(hour(t) < 10){
    tempo[0] = display.encodeDigit(0);
    if(seg == true)
      tempo[1] = display.encodeDigit(hour(t)) + 0b10000000;
    else
      tempo[1] = display.encodeDigit(hour(t));
  } else{
    tempo[0] = display.encodeDigit(hour(t) / 10);
    if(seg == true)
      tempo[1] = display.encodeDigit(hour(t) % 10) + 0b10000000;
     else
      tempo[1] = display.encodeDigit(hour(t) % 10);
  }
  if(minute(t) < 10){
    tempo[2] = display.encodeDigit(0);
    tempo[3] = display.encodeDigit(minute(t));
  } else{
    tempo[2] = display.encodeDigit(minute(t) / 10);
    tempo[3] = display.encodeDigit(minute(t) % 10);
  }
  display.setSegments(tempo);
}
