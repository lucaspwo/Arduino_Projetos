//Reads a PWM signal's duty cycle and frequency.
#define READ_PIN 7

#define PWM_OUTPUT 10

static double duty;
static double freq;
static long highTime = 0;
static long lowTime = 0;
static long tempPulse;

void setup(){
pinMode(READ_PIN,INPUT);
Serial.begin(9600);
analogWrite(PWM_OUTPUT,230);
}

void loop(){
readPWM(READ_PIN);
Serial.println(freq);
Serial.println(duty);
//delay(1000);
}

//Takes in reading pins and outputs pwm frequency and duty cycle.
void readPWM(int readPin){
highTime = 0;
lowTime = 0;

tempPulse = pulseIn(readPin,HIGH);
if(tempPulse>highTime){
highTime = tempPulse;
}

tempPulse = pulseIn(readPin,LOW);
if(tempPulse>lowTime){
lowTime = tempPulse;
}

freq = ((double) 1000000)/(double (lowTime+highTime));
duty = (100*(highTime/(double (lowTime+highTime))));
}
