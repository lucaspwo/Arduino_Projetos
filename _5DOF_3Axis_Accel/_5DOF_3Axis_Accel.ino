int x, y, z;  // X and Y in-plane sensing

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
}

void loop()
{
  x = analogRead(0);       // read analog input pin 0
  y = analogRead(1);       // read analog input pin 1
  z = analogRead(2);
  Serial.print("x, y, z: ");
  Serial.print(x, DEC);    // print the rotational rate in the X axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.print(y, DEC);  // print the rotational rate in the Y axis
  Serial.print(" ");
  Serial.println(z, DEC);
  delay(100);              // wait 100ms for next reading
}
