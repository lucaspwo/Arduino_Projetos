#define SENSOR A4
#define SENSOR2 A5

int sensorValue = 0;
int sensorvalue2 = 0;
int G1 = 13;
int G2 = 12;
int Y1 = 11;
int Y2 = 10;
int R1 = 9;
int R2 = 8; 

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT); //Verde
  pinMode(12, OUTPUT); //Amarelo1
  pinMode(11, OUTPUT); //Amarelo2
  pinMode(10, OUTPUT); //Vermelho1
  pinMode(9, OUTPUT); //Vermelho2
  pinMode(8, OUTPUT); //Vermelho3
}

void loop()
{
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if(sensorValue >= 500 && sensorValue <= 600)
  {
    digitalWrite(R2, HIGH);
    digitalWrite(R1, HIGH);
    digitalWrite(Y2, HIGH);
    digitalWrite(Y1, HIGH);
    digitalWrite(G2, HIGH);
    digitalWrite(G1, HIGH);
  }else if(sensorValue < 500 && sensorValue >= 400)
         {  
            digitalWrite(R2, LOW);
            digitalWrite(R1, HIGH);
            digitalWrite(Y2, HIGH);
            digitalWrite(Y1, HIGH);
            digitalWrite(G2, HIGH);
            digitalWrite(G1, HIGH);
        }else if(sensorValue < 400 && sensorValue >= 300)
              {
                  digitalWrite(R2, LOW);
                  digitalWrite(R1, LOW);
                  digitalWrite(Y2, HIGH);
                  digitalWrite(Y1, HIGH);
                  digitalWrite(G2, HIGH);
                  digitalWrite(G1, HIGH);
              }else if(sensorValue < 300 && sensorValue >= 200)
		    {
                        digitalWrite(R2, LOW);
                        digitalWrite(R1, LOW);
                        digitalWrite(Y2, LOW);
                        digitalWrite(Y1, HIGH);
                        digitalWrite(G2, HIGH);
                        digitalWrite(G1, HIGH);
		     }else if(sensorValue < 200 && sensorValue >= 100)
			    {
                                digitalWrite(R2, LOW);
                                digitalWrite(R1, LOW);
                                digitalWrite(Y2, LOW);
                                digitalWrite(Y1, LOW);
                                digitalWrite(G2, HIGH);
                                digitalWrite(G1, HIGH);
       			    }else if(sensorValue < 100 && sensorValue >= 50)
				  {
			      	      digitalWrite(R2, LOW);
				      digitalWrite(R1, LOW);
				      digitalWrite(Y2, LOW);
				      digitalWrite(Y1, LOW);
				      digitalWrite(G2, LOW);
				      digitalWrite(G1, HIGH);				
						}else if(sensorValue < 50 && sensorValue >= 0)
                        				  {
                        			      	      digitalWrite(R2, LOW);
                        				      digitalWrite(R1, LOW);
                        				      digitalWrite(Y2, LOW);
                        				      digitalWrite(Y1, LOW);
                        				      digitalWrite(G2, LOW);
                        				      digitalWrite(G1, LOW);				
                        						}
  delay(500); 
}
