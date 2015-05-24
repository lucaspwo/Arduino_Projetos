#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9};
byte ip[] = {75,4,23,64};
char rootFileName[] = "index.html";
EthernetServer server (8081);


