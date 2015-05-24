/*
 * Use SoftwareSerial to talk to BlueSMiRF module
 * note pairing code is 1234
 */

void setup()
{
  Serial.begin(9600);
  Serial2.begin(115200);      // initialize the HARDWARE serial port
  Serial.println("Serial ready");
  Serial2.println("Bluetooth ready");
}

void loop()
{
  if (Serial2.available())
  {
    char c = (char)Serial2.read();
    Serial.write(c);
  }
  if (Serial.available())
  {
    char c = (char)Serial.read();
    Serial2.write(c);
  }
}
