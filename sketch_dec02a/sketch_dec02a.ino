#include <StopWatch.h>

#define threshold  400

StopWatch sw1,sw2,sw3,sw4,sw5;
float t1=0,t2=0,t3=0,t4=0,t5=0;
float to1=0,to2=0,to3=0,to4=0,to5=0;
boolean c1=false,c2=false,c3=false;
boolean s1=false,s2=false,s3=false,s4=false,s5=false;

void setup(){
  Serial.begin(115200);
}

void loop(){
  //if(digitalRead(10)){
    /*if(c1 == false){
      if((analogRead(A0) < threshold || analogRead(A4) < threshold)){
        sw1.start();
        c1 = true;
      }
    }*/
    /*if(c2 == false){
      if((analogRead(A1) < threshold || analogRead(A3) < threshold)){
        sw2.start();
        c2 = true;
      }
    }*/
        
    if(analogRead(A2) < threshold && s3 == true){
      s3 = false;
      to3 = t3;
      t3 = sw3.elapsed();
      Serial.print("3: ");
      Serial.println((t3 - to3));
      s4 = true;
      s2 = true; 
    }
    if(analogRead(A3) < threshold && s4 == true){
      /*s4 = false;
      to4 = t4;
      t4 = sw4.elapsed();*/
      //Serial.print("4: ");
      //Serial.println((t4 - to4));
      s3 = true;
    }
    if(analogRead(A1) < threshold && s2 == true){
      /*s4 = false;
      to4 = t4;
      t4 = sw4.elapsed();*/
      //Serial.print("4: ");
      //Serial.println((t4 - to4));
      s3 = true;
    }
    
    if(c3 == false){
      if(analogRead(A2) < threshold){
        sw3.start();
        Serial.println("SW3 begin");
        c3 = true;
        s3 = true;
      }
    }
  //}
}
