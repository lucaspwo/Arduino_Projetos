/*
 * Use SoftwareSerial to talk to BlueSMiRF module
 * note pairing code is 1234
 */

void setup()
{
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  //Serial.begin(9600);
  Serial2.begin(115200);      // initialize the HARDWARE serial port
  //Serial.println("Serial ready");
  Serial2.println("Bluetooth ready");
}

void loop()
{
  if (Serial2.available())
  {
    char c = (char)Serial2.read();
    //Serial.write(c);
    if (c == '2')
    {
      digitalWrite(10, LOW);
      digitalWrite(12, HIGH);
    }
    if (c == '3')
    {
      digitalWrite(10, HIGH);
      digitalWrite(12, LOW);
    }
    if (c == '4')
    {
      digitalWrite(10, LOW);
      digitalWrite(12, LOW);
    }
  }
  /*if (Serial.available())
  {
    //char c = (char)Serial.read();
    //Serial2.write(c);
  }*/
}
