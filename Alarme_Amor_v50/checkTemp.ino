float checkTemp(){                //verifica a temperatura
  float media=0;
  for(int i=0; i<1000; i++){      //faz mil leituras
    media = media + analogRead(3);
  }
  media = media/1000;             //realiza a media
  media = media * 0.41015625;     //(4,20 volts / 1024) * 100
  return(media);
}
