#define d1 6
#define d2 5
#define d3 9
#define d4 3
#define d5 10

int fi1, fi2, fi3 = 0;
int fo1, fo2, fo3 = 170;

void setup(){
    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(d3, OUTPUT);
    pinMode(d4, OUTPUT);
    pinMode(d5, OUTPUT);
}

void loop(){
    int i = 0;
    fi1 = 0;
    fi2 = 0;
    fi3 = 0;
    
    for(i=0; i<192; i+=8){
        
        fadein1(d1);
        
        if(i >= 64){
            fadein2(d2, d3);
            
            if(i >= 128){
                fadein3(d4, d5);
            }
        }
    }
    
    fo1 = 128;
    fo2 = 128;
    fo3 = 128;
    
    for(i=192; i>0; i-=8){
        
        fadeout1(d1);
        
        if(i <= 128){
            fadeout2(d2, d3);
            
            if(i <= 64){
                fadeout3(d4, d5);
            }
        }
    }
}

void fadein1(int led){
    while(fi1 < 128){
        fi1+=8;
        analogWrite(led, fi1);
        delay(10);
    }
}

void fadein2(int led1, int led2){
    while(fi2 < 128){
        fi2+=8;
        analogWrite(led1, fi2);
        analogWrite(led2, fi2);
        delay(10);
    }
}

void fadein3(int led1, int led2){
    while(fi3 < 128){
        fi3+=8;
        analogWrite(led1, fi3);
        analogWrite(led2, fi3);
        delay(10);
    }
}

void fadeout1(int led){
    while(fo1 > 0){
        fo1-=8;
        analogWrite(led, fo1);
        delay(10);
    }
}

void fadeout2(int led1, int led2){
    while(fo2 > 0){
        fo2-=8;
        analogWrite(led1, fo2);
        analogWrite(led2, fo2);
        delay(10);
    }
}

void fadeout3(int led1, int led2){
    while(fo3 > 0){
        fo3-=8;
        analogWrite(led1, fo3);
        analogWrite(led2, fo3);
        delay(10);
    }
}
