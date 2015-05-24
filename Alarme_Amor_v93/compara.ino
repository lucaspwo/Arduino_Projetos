void compara(String *hora, String *minuto){
  String Hora, Minuto;
  Hora += ajustaZero(dado2);
  Minuto += ajustaZero(dado3);
  if(Hora == *hora){
    if(Minuto == *minuto){
      if(toca == true){
        return;
      }
      if(toca == false && alarme == true){
        apita();
        toca = true;
        if(zzz == 0 || zzz == 1 || zzz == 2){
          snooze();
        }
        if(zzz == 3){
          Wire.beginTransmission(ROM);
          Wire.write(0x00);
          Wire.write(0x00);
          Wire.write((byte)65);
          delay(10);
          Wire.endTransmission();
          zzz = 0;
        }
        imprimeTela();
        return;
      }
    }
  }
}
