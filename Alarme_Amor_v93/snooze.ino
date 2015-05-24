void snooze(){
	boolean choiceS = true, choiceN = false;
	analogWrite(PWR, 255);
	lcd.clear();
	lcd.setCursor(0,0);
	if(zzz == 0){
		char reg = '9';
		lcd.write("Soneca: 10 min?");
		lcd.setCursor(0,1);
		lcd.write((uint8_t)1);
		lcd.write("Sim  Nao   ( )");
		lcd.setCursor(7,1);
		lcd.write((uint8_t)6);
		lcd.setCursor(13,1);
		lcd.write(reg);
		while(digitalRead(ENT) == true && reg != 47){
			if((digitalRead(PCI) == false || digitalRead(PBA) == false) && choiceS == true){
				lcd.clear();
				lcd.setCursor(0,0);
				lcd.write("Soneca: 10 min?");
				lcd.setCursor(0,1);
				lcd.write(" Sim  Nao   ( )");
				lcd.setCursor(7,1);
				lcd.write((uint8_t)6);
				lcd.setCursor(5,1);
				lcd.write((uint8_t)1);
				lcd.setCursor(13,1);
				lcd.write(reg);
				choiceS = false;
				choiceN = true;
			}
			delay(200);
			if((digitalRead(PCI) == false || digitalRead(PBA) == false) && choiceN == true){
				lcd.clear();
				lcd.setCursor(0,0);
				lcd.write("Soneca: 10 min?");
				lcd.setCursor(0,1);
				lcd.write(" Sim  Nao   ( )");
				lcd.setCursor(7,1);
				lcd.write((uint8_t)6);
				lcd.setCursor(0,1);
				lcd.write((uint8_t)1);
				lcd.setCursor(13,1);
				lcd.write(reg);
				choiceS = true;
				choiceN = false;
			}
			delay(200);
			if(digitalRead(ENT) == false && choiceS == true){
				break;
			}
			if(digitalRead(ENT) == false && choiceN == true){
				break;
			}
			lcd.setCursor(13,1);
			lcd.write(reg);
			reg--;
			delay(600);
		}
		if(choiceS == true){
			Wire.beginTransmission(ROM);
			Wire.write(0x00);
			Wire.write(0x00);
			Wire.endTransmission();
			delay(10);
			Wire.requestFrom(ROM, 3);
			byte dado1 = Wire.read();
			dado2 = Wire.read();
			dado3 = Wire.read();
			delay(10);
			Wire.endTransmission();

			int Hor = (int)dado2, Min = (int)dado3;
			if(Min >= 50){
				if(Hor == 23){
					Hor = 0;
				} else{
					Hor++;
				}
				if(Min == 50){
					Min = 0;
				} else if(Min == 51){
					Min = 1;
				} else if(Min == 52){
					Min = 2;
				} else if(Min == 53){
					Min = 3;
				} else if(Min == 54){
					Min = 4;
				} else if(Min == 55){
					Min = 5;
				} else if(Min == 56){
					Min = 6;
				} else if(Min == 57){
					Min = 7;
				} else if(Min == 58){
					Min = 8;
				} else if(Min == 59){
					Min = 9;
				} 
			} else{
				Min = Min+10;
			}

			Wire.beginTransmission(ROM);
  			Wire.write(0x00);
 			Wire.write(0x00);
  			Wire.write((byte)66);
  			Wire.write((byte)Hor);
  			Wire.write((byte)Min);
  			delay(10);
  			Wire.endTransmission();
		}
		if(choiceN == true){
			zzz = 3;
			return;
		}
	} else if(zzz == 1){
		char reg = '9';
		lcd.write("Soneca: 5 min?");
		lcd.setCursor(0,1);
		lcd.write((uint8_t)1);
		lcd.write("Sim  Nao   ( )");
		lcd.setCursor(10,1);
		lcd.write((uint8_t)6);
		lcd.setCursor(5,1);
		lcd.write(reg);
		while(digitalRead(ENT) == true && reg != 47){
			if((digitalRead(PCI) == false || digitalRead(PBA) == false) && choiceS == true){
				lcd.clear();
				lcd.setCursor(0,0);
				lcd.write("Soneca: 5 min?");
				lcd.setCursor(0,1);
				lcd.write(" Sim  Nao   ( )");
				lcd.setCursor(7,1);
				lcd.write((uint8_t)6);
				lcd.setCursor(5,1);
				lcd.write((uint8_t)1);
				lcd.setCursor(13,1);
				lcd.write(reg);
				choiceS = false;
				choiceN = true;
			}
			delay(200);
			if((digitalRead(PCI) == false || digitalRead(PBA) == false) && choiceN == true){
				lcd.clear();
				lcd.setCursor(0,0);
				lcd.write("Soneca: 5 min?");
				lcd.setCursor(0,1);
				lcd.write(" Sim  Nao   ( )");
				lcd.setCursor(7,1);
				lcd.write((uint8_t)6);
				lcd.setCursor(0,1);
				lcd.write((uint8_t)1);
				lcd.setCursor(13,1);
				lcd.write(reg);
				choiceS = true;
				choiceN = false;
			}
			delay(200);
			if(digitalRead(ENT) == false && choiceS == true){
				break;
			}
			if(digitalRead(ENT) == false && choiceN == true){
				break;
			}
			lcd.setCursor(13,1);
			lcd.write(reg);
			reg--;
			delay(600);
		}
		if(choiceS == true){
			Wire.beginTransmission(ROM);
			Wire.write(0x00);
			Wire.write(0x00);
			Wire.endTransmission();
			delay(10);
			Wire.requestFrom(ROM, 3);
			byte dado1 = Wire.read();
			dado2 = Wire.read();
			dado3 = Wire.read();
			delay(10);
			Wire.endTransmission();

			int Hor = (int)dado2, Min = (int)dado3;
			if(Min >= 55){
				if(Hor == 23){
					Hor = 0;
				} else{
					Hor++;
				}
				if(Min == 55){
					Min = 60;
				} else if(Min == 56){
					Min = 1;
				} else if(Min == 57){
					Min = 2;
				} else if(Min == 58){
					Min = 3;
				} else if(Min == 59){
					Min = 4;
				} 
			} else{
				Min = Min+5;
			} 

			Wire.beginTransmission(ROM);
  			Wire.write(0x00);
 			Wire.write(0x00);
  			Wire.write((byte)66);
  			Wire.write((byte)Hor);
  			Wire.write((byte)Min);
  			delay(10);
  			Wire.endTransmission();
		}
		if(choiceN == true){
			zzz = 3;
			return;
		}
	} else if(zzz == 2){
		toca = false;
		apita();
	}

	zzz++;
}