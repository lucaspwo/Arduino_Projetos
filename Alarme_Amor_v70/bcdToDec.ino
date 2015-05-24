byte bcdToDec(byte val){              //funcao para converter valores de BCD para decimal
  return ( (val/16*10) + (val%16) );
}
