#include <SoftwareSerial.h>
 char inchar; //Will hold the incoming character from the Serial Port.
 SoftwareSerial cell(2,3); //Create a 'fake' serial port. Pin 2 is the Rx pin, pin 3 is the Tx pin.

 int led4 = 12;

 void setup() {
   // prepare the digital output pins
   pinMode(led4, OUTPUT);
   digitalWrite(led4, LOW);
   //Initialize GSM module serial port for communication.
   cell.begin(9600);
   delay(65000); // give time for GSM module to register on network etc.
   digitalWrite(led4, HIGH);
   cell.println("AT+CMGF=1"); // set SMS mode to text
   delay(200);
   cell.println("AT+CNMI=3,3,0,0"); // set module to send SMS data to serial out upon receipt 
   delay(200);
 }

 void loop() {
   //If a character comes in from the cellular module...
   if(cell.available() >0) {
     inchar=cell.read(); 
     if (inchar=='s'){
       delay(10);
       inchar=cell.read();
       
       if (inchar=='t'){
         delay(10);
         inchar=cell.read();
                  
         if (inchar=='a'){
           delay(10);
           inchar=cell.read(); 
           
           if (inchar=='t'){
             delay(10);
             inchar=cell.read(); 
             
             if (inchar=='u'){
               delay(10);
               inchar=cell.read();
               
               if (inchar=='s'){
                 digitalWrite(led4, LOW);
                 cell.println("AT+CMGS=1");
                 cell.print("AT+CMGS=");
                 cell.print(32, DEC);
                 cell.print("08499213787");
                 cell.println(32, DEC);
                 delay(10);
                 cell.println("Hello World");
                 cell.println(26, DEC);
               }
             }
           }
           cell.println("AT+CMGD=1,4"); // delete all SMS
         }
       }
     }
   }
 }
