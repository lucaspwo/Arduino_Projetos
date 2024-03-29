//This is the basic SDFat Webserver sketch, without any modifications
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <Ethernet.h>

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9};
byte ip[] = {
  75,4,207,78};
char rootFileName[] = "index.htm";  //root file name is what the homepage will be.
EthernetServer server(8989);

Sd2Card card;  //SD Stuff
SdVolume volume;
SdFile root;
SdFile file;

#define error(s) error_P(PSTR(s))  //SD card errors stored in Program memory
void error_P(const char* str) {  //Error function
  PgmPrint("error: ");
  SerialPrintln_P(str);
  if (card.errorCode()) {
    PgmPrint("SD error: ");
    Serial.print(card.errorCode(), HEX);
    Serial.print(',');
    Serial.println(card.errorData(), HEX);
  }
  while(1);
}

void setup() {  //setup stuff
  Serial.begin(9600);
  PgmPrint("Free RAM: ");
  Serial.println(FreeRam());
  pinMode(53, OUTPUT);
  digitalWrite(10, HIGH);
  if (!card.init(SPI_FULL_SPEED, 4)) error("card.init failed!");  //If you are having errors when reading from the SD card, change FULL to HALF
  if (!volume.init(&card)) error("vol.init failed!");
  PgmPrint("Volume is FAT");
  Serial.println(volume.fatType(),DEC);
  Serial.println();
  if (!root.openRoot(&volume)) error("openRoot failed");
  PgmPrintln("Files found in root:");
  root.ls(LS_DATE | LS_SIZE);
  Serial.println();
  PgmPrintln("Files found in all dirs:");
  root.ls(LS_R);
  Serial.println();
  PgmPrintln("Done");
  Ethernet.begin(mac, ip);
  server.begin();
}
#define BUFSIZ 100  //defines the buffer size.  100 gives plenty of room.  reduce size if more ram is needed.

void loop()
{
  char clientline[BUFSIZ];
  char *filename;
  int index = 0;
  int image = 0;
  EthernetClient client = server.available();
  if (client) {
    boolean current_line_is_blank = true;
    index = 0;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c != '\n' && c != '\r') {
          clientline[index] = c;
          index++;
          if (index >= BUFSIZ)
            index = BUFSIZ -1;
          continue;
        }
        clientline[index] = 0;
        filename = 0;
        Serial.println(clientline);
        if (strstr(clientline, "GET / ") != 0) {  //If you are going to the homepage, the filename is set to the rootFileName
          filename = rootFileName;
        }
        if (strstr(clientline, "GET /") != 0) {
          if (!filename) filename = clientline + 5;  //gets rid of the GET / in the filename
          (strstr(clientline, " HTTP"))[0] = 0;  //gets rid of everything from HTTP to the end.
          Serial.println(filename);
          if (! file.open(&root, filename, O_READ)) {  //if the file doesn't exist a 404 is sent
            client.println("HTTP/1.1 404 Not Found");
            client.println("Content-Type: text/html");
            client.println();
            client.println("<h2>File Not Found!</h2>");
            break;
          }
          Serial.println("Opened!");
          client.println("HTTP/1.1 200 OK");
          if (strstr(filename, ".htm") != 0)  //Sets content type.
            client.println("Content-Type: text/html");
          else if (strstr(filename, ".css") != 0)
            client.println("Content-Type: text/css");
          else if (strstr(filename, ".png") != 0)
            client.println("Content-Type: image/png");
          else if (strstr(filename, ".jpg") != 0)
            client.println("Content-Type: image/jpeg");
          else if (strstr(filename, ".gif") != 0)
            client.println("Content-Type: image/gif");
          else if (strstr(filename, ".3gp") != 0)
            client.println("Content-Type: video/mpeg");
          else if (strstr(filename, ".pdf") != 0)
            client.println("Content-Type: application/pdf");
          else if (strstr(filename, ".js") != 0)
            client.println("Content-Type: application/x-javascript");
          else if (strstr(filename, ".xml") != 0)
            client.println("Content-Type: application/xml");
          else
            client.println("Content-Type: text");
          client.println();
          int16_t c;
          while ((c = file.read()) >= 0) {
              client.write((char)c);  //sends file to website client
          }
          file.close();
        } 
        else {
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<h2>File Not Found!</h2>");
        }
        break;
      }
    }
    delay(1);
    client.stop();
  }
}
