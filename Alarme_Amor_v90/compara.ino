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
        Wire.beginTransmission(ROM);
        Wire.write(0x00);
        Wire.write(0x00);
        Wire.write((byte)65);
        delay(10);
        Wire.endTransmission();
        imprimeTela();
        return;
      }
    }
  }
}
