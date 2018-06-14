#include <SoftwareSerial.h>
#include<CountUpDownTimer.h>
#include <serLCD.h>

int pin = 7;
int ser;
bool bL1 = false, bL2 = false, bA1 = false, bA2 = false, bM1 = false, bM2 = false, bR1 = false, bR2 = false;
String disp;
serLCD lcd(pin);
CountUpDownTimer T1(UP, HIGH); // Default precision is HIGH, but you can change it to also be LOW
CountUpDownTimer T2(UP, HIGH);
CountUpDownTimer T3(UP, HIGH);
CountUpDownTimer T4(UP, HIGH);

void setup()
{
  lcd.clear();
  Serial.begin(115200);
  T1.SetTimer(0,0,0);     //start at 1 minute (USE FOR: DOWN ONLY)
  T2.SetTimer(0,0,0);
  T3.SetTimer(0,0,0);
  T4.SetTimer(0,0,0);
}

void loop()
{
  if(Serial.available() > 0){
    ser = Serial.read();
    if(ser == 'L'){
      if(bL1 == false && bL2 == false){
        bL1 = true;
        T1.StartTimer();
      } else if(bL1 == true && bL2 == false){
        bL2 = true;
        T1.PauseTimer();
      } else if(bL1 == true && bL2 == true){
        bL2 = false;
        T1.ResumeTimer();
      }
    }
    else if(ser == 'A'){
      if(bA1 == false && bA2 == false){
        bA1 = true;
        T2.StartTimer();
      } else if(bA1 == true && bA2 == false){
        bA2 = true;
        T2.PauseTimer();
      } else if(bA1 == true && bA2 == true){
        bA2 = false;
        T2.ResumeTimer();
      }
    }
    else if(ser == 'M'){
      if(bM1 == false && bM2 == false){
        bM1 = true;
        T3.StartTimer();
      } else if(bM1 == true && bM2 == false){
        bM2 = true;
        T3.PauseTimer();
      } else if(bM1 == true && bM2 == true){
        bM2 = false;
        T3.ResumeTimer();
      }
    }
    if(ser == 'R'){
      if(bR1 == false && bR2 == false){
        bR1 = true;
        T4.StartTimer();
      } else if(bR1 == true && bR2 == false){
        bR2 = true;
        T4.PauseTimer();
      } else if(bR1 == true && bR2 == true){
        bR2 = false;
        T4.ResumeTimer();
      }
    }
  }

  T1.Timer();   // run the timer
  T2.Timer();
  T3.Timer();
  T4.Timer();
  
  if (T1.TimeHasChanged() || T2.TimeHasChanged() || T3.TimeHasChanged() || T4.TimeHasChanged()){ // this prevents the time from being constantly shown.
    lcd.clear();
    disp = "L:";
    Serial.print("L:");
    Serial.print(T1.ShowHours());
    if(T1.ShowHours() < 10){
      disp = disp + "0";
      disp = disp + T1.ShowHours();
    } else{
      disp = disp + T1.ShowHours();
    }
    Serial.print(":");
    disp = disp + ":";
    Serial.print(T1.ShowMinutes());
    if(T1.ShowMinutes() < 10){
      disp = disp + "0";
      disp = disp + T1.ShowMinutes();
    } else{
      disp = disp + T1.ShowMinutes();
    }
    Serial.print(":");
    Serial.println(T1.ShowSeconds());

    disp = disp + " ";

    disp = disp + "A:";
    Serial.print("A:");
    Serial.print(T2.ShowHours());
    if(T2.ShowHours() < 10){
      disp = disp + "0";
      disp = disp + T2.ShowHours();
    } else{
      disp = disp + T2.ShowHours();
    }
    Serial.print(":");
    disp = disp + ":";
    Serial.print(T2.ShowMinutes());
    if(T2.ShowMinutes() < 10){
      disp = disp + "0";
      disp = disp + T2.ShowMinutes();
    } else{
      disp = disp + T2.ShowMinutes();
    }
    Serial.print(":");
    Serial.println(T2.ShowSeconds());

    disp = disp + " ";

    disp = disp + "M:";
    Serial.print("M:");
    Serial.print(T3.ShowHours());
    if(T3.ShowHours() < 10){
      disp = disp + "0";
      disp = disp + T3.ShowHours();
    } else{
      disp = disp + T3.ShowHours();
    }
    Serial.print(":");
    disp = disp + ":";
    Serial.print(T3.ShowMinutes());
    if(T3.ShowMinutes() < 10){
      disp = disp + "0";
      disp = disp + T3.ShowMinutes();
    } else{
      disp = disp + T3.ShowMinutes();
    }
    Serial.print(":");
    Serial.println(T3.ShowSeconds());

    disp = disp + " ";

    disp = disp + "R:";
    Serial.print("R:");
    Serial.print(T4.ShowHours());
    if(T4.ShowHours() < 10){
      disp = disp + "0";
      disp = disp + T4.ShowHours();
    } else{
      disp = disp + T4.ShowHours();
    }
    Serial.print(":");
    disp = disp + ":";
    Serial.print(T4.ShowMinutes());
    if(T4.ShowMinutes() < 10){
      disp = disp + "0";
      disp = disp + T4.ShowMinutes();
    } else{
      disp = disp + T4.ShowMinutes();
    }
    Serial.print(":");
    Serial.println(T4.ShowSeconds());

    Serial.println();
    lcd.print(disp);
  }
}
