byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
