/* Example program for from IRLib – an Arduino library for infrared encoding and decoding
 * Version 1.3   January 2014
 * Copyright 2014 by Chris Young http://cyborg5.com
 * Based on original example sketch for IRremote library 
 * Version 0.11 September, 2009
 * Copyright 2009 Ken Shirriff
 * http://www.righto.com/
 */
#include <IRLib.h>

IRsend My_Sender;

unsigned int Signal_LED_0[] = {4460,4308,596,1580,592,496,596,1584,596,1580,596,496,592,1584,596,496,596,1584,616,476,620,1556,596,492,596,496,596,1580,596,492,620,1564,592,496,596,1584,592,1580,596,1584,592,1580,620,472,592,1584,596,496,620,1560,596,496,620,472,592,496,596,496,596,1584,620,468,620,1564,592,500,616,1560,592,500,592,1584,620,472,620,472,616,1560,592,496,596,1584,620,476,592,1580,620,468,596,1588,592,1580,620,472,592,1584,620,476,564,5192,4436,4320,620,1556,596,496,596,1584,592,1580,620,472,596,1580,620,476,592,1588,592,496,596,1580,600,496,592,492,600,1580,592,496,596,1584,592,500,620,1556,596,1576,600,1580,592,1580,620,472,596,1584,592,496,596,1588,592,500,592,496,596,496,596,496,592,1584,620,472,596,1584,592,500,616,1560,592,496,620,1560,596,496,620,468,596,1580,592,500,592,1588,620,472,596,1580,596,496,596,1580,620,1556,620,472,620,1556,600,496,564}; //AnalysIR Batch Export - RAW
unsigned int Signal_Oscilar_1[] = {4480,4300,616,1556,620,472,620,1560,616,1560,620,472,616,476,616,1556,616,480,616,476,588,1592,616,476,616,476,612,1560,620,1556,616,476,588,1592,616,480,588,1584,592,1584,592,500,592,1584,592,500,592,1588,592,1588,584,1592,596,496,616,472,592,1584,592,500,592,1584,592,500,564,532,560,1616,568,1612,560,1612,592,500,564,524,568,524,592,500,560,528,536,560,560,532,560,528,560,1620,560,1612,564,1612,560,1612,536,1644,608,5160,4368,4384,536,1640,532,556,536,1648,532,1640,536,556,536,552,536,1640,532,556,536,560,536,1644,532,556,536,556,532,1640,536,1640,564,528,536,1640,536,560,536,1636,536,1644,532,556,536,1640,568,524,536,1640,536,1644,532,1648,564,528,536,552,536,1640,532,556,536,1648,560,528,532,560,536,1648,560,1612,536,1636,536,556,536,556,532,556,536,556,536,560,528,560,536,556,536,556,536,1640,536,1636,536,1644,532,1640,536,1640,632}; //AnalysIR Batch Export - RAW
unsigned int Signal_Liga_23_auto_2[] = {4492,4288,648,1528,648,444,648,1532,644,1532,648,448,616,476,620,1552,648,448,620,476,620,1560,644,448,616,476,620,1552,648,1532,644,448,644,1536,644,452,620,472,644,448,620,1556,620,1556,624,1552,644,1536,644,1532,644,1540,644,1532,648,1528,624,472,620,468,620,472,648,444,620,476,620,476,640,1536,620,472,620,1560,624,1552,644,452,616,476,616,472,620,1560,644,452,612,1564,648,444,644,448,644,1528,652,1528,644,1532,584,5196,4488,4276,648,1532,644,448,644,1532,648,1532,644,448,644,444,648,1528,652,444,644,452,644,1532,648,448,644,448,640,1536,644,1528,648,448,644,1536,648,452,644,444,644,448,644,1528,648,1532,644,1528,652,1528,624,1552,624,1564,620,1552,624,1556,644,452,644,444,620,472,644,448,644,452,620,468,648,1532,624,468,648,1532,624,1560,640,448,620,472,620,472,644,1532,644,452,640,1536,648,444,644,452,640,1532,648,1528,648,1532,576}; //AnalysIR Batch Export - RAW

int khz=38; //NB Change this default value as neccessary to the correct carrier frequency

void setup()
{
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(7) == HIGH){
    My_Sender.IRsendRaw::send(Signal_Liga_23_auto_2, sizeof(Signal_Liga_23_auto_2)/sizeof(int), khz); //AnalysIR Batch Export (IRLib) - RAW
    delay(50);
    My_Sender.IRsendRaw::send(Signal_Oscilar_1, sizeof(Signal_Oscilar_1)/sizeof(int), khz); //AnalysIR Batch Export (IRLib) - RAW
    delay(50);
    My_Sender.IRsendRaw::send(Signal_LED_0, sizeof(Signal_LED_0)/sizeof(int), khz); //AnalysIR Batch Export (IRLib) - RAW  
    Serial.println("Foi");
    delay(2000);
  }
}





