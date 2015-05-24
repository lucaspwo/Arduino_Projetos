void compara(String *hora, String *minuto){
  String Hora, Minuto;
  Hora += ajustaZero(dado2);
  Minuto += ajustaZero(dado3);
  if(Hora == *hora){
    if(Minuto == *minuto){
      if(toca == false){
        apita();
        toca = true;
        imprimeTela();
        return;
      }
      else{
        return;
      }
    }
  }
}
