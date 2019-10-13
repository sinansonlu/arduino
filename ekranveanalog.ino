#include <Adafruit_SSD1306.h>
#include <splash.h>

Adafruit_SSD1306 ekran(128, 64, &Wire, -1);

int ek_x;
int ek_y;

int ciz_x;
int ciz_y;

int sayi = 2;
bool yukariMi = true;

void setup() {
  // put your setup code here, to run once:
  ekran.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  // analoglardan oku
  ek_x = analogRead(A0);
  ek_y = analogRead(A1);

  // hesapla
  ciz_x = ciz_x + ((ek_x - 512) / 128);
  ciz_y = ciz_y - ((ek_y - 512) / 128);

  if (yukariMi) {
    sayi++;
    if (sayi > 20) {
      yukariMi = false;
    }
  } else {
    sayi--;
    if (sayi < 1) {
      yukariMi = true;
    }
  }

  // ekrana yazıyı yaz
  ekran.clearDisplay();
  ekran.setTextColor(WHITE);
  ekran.setTextSize(1);
  ekran.setCursor(ciz_x, ciz_y);
  ekran.print("Selam!");
  ekran.fillCircle(ciz_x, ciz_y, sayi, INVERSE);

  // çizgiyi belirle
  ekran.drawLine(0, 0, 127, 63, WHITE);
  ekran.display();
}
