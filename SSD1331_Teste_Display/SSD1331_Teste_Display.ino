#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

// Defina os pinos de conexão SPI para o seu display
#define sclk 13  // SCK
#define mosi 11  // MOSI
#define cs   10  // CS (Chip Select)
#define rst   9  // Reset
#define dc    8  // D/C (Data/Command)

// Definicoes de cores para o display
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

// Inicializa o display
Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst);

void setup() {
  Serial.begin(9600);
  display.begin();

  display.fillScreen(BLACK);
  delay(500);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Teste SSD1331");

  display.setTextColor(RED);
  display.setCursor(0, 15);
  display.println("Texto em vermelho");

  display.drawRect(0, 30, 50, 30, GREEN);
  display.fillRect(60, 30, 50, 30, BLUE);

  display.drawLine(0, 0, 95, 63, YELLOW);
}

void loop() {
  // nada no loop por enquanto
}
