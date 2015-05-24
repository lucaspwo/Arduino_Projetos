String ajustaZero(byte dado){         //funcao para adicionar um zero na saida do numero
  String dadoAjustado;
  if (dado < 10){
    dadoAjustado += "0";
  }
  dadoAjustado += dado; 
  
  return dadoAjustado; 
}
