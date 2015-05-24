int input1=11;
int input2=10;
int enable1=13;
int enable2=12;
void setup()
{
    pinMode(input1,OUTPUT);
    pinMode(enable1,OUTPUT);
    pinMode(input2,OUTPUT);
    pinMode(enable2,OUTPUT);
    Serial.begin(9600);
}
void loop()
{
  char value=Serial.read();
  
  if(value=='o')
  {
   analogWrite(input1,250);
    digitalWrite(enable1, HIGH);
    analogWrite(input2,250);
    digitalWrite(enable2, HIGH); 
  }else
  if(value=='d')
  {
    analogWrite(input1,0);
    digitalWrite(enable1, LOW);
    analogWrite(input2,0);
    digitalWrite(enable2, LOW); 
  }else
  if(value=='r')
  {
    analogWrite(input1,250);
    digitalWrite(enable1, HIGH);
    analogWrite(input2,10);
    digitalWrite(enable2, HIGH); 
  }else
  if(value=='l')
  {
    analogWrite(input1,10);
    digitalWrite(enable1, HIGH);
    analogWrite(input2,250);
    digitalWrite(enable2, HIGH); 
  }
   
      
       
    
  
}
