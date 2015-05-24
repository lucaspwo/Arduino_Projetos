//redefinindo os pinos
#define d1 3
#define d2 5
#define d3 6
#define d4 9
#define d5 10
#define d6 11

void setup()
{
	//definindo as saidas analogicas
	Serial.begin(9600);
	pinMode(d1, OUTPUT);
	pinMode(d2, OUTPUT);
	pinMode(d3, OUTPUT);
	pinMode(d4, OUTPUT);
	pinMode(d5, OUTPUT);
	pinMode(d6, OUTPUT);
	
}

void loop()
{
	fade(d1, d2);
	fade(d2, d3);
	fade(d3, d4);
	fade(d4, d5);
	fade(d5, d6);
	fade(d6, d1);
	
}

void fade(int diodo1,int diodo2)
{
	int sobe=0;
	int dece=254;
	for( ;  sobe<=254 && dece>=0 ; sobe++, dece-- )
	{
		analogWrite(diodo1, dece);
		analogWrite(diodo2, sobe);
		delay(10);
	}
}
