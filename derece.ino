#include <math.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 ekran(128, 64, &Wire, -1);

double son;

double temps[16];
int scr[128];

int temps_i;
int scr_i;

void setup() {
  temps_i = 0;
  scr_i = 0;
  son = 0;

  for (int i = 0; i < 16; i++) {
    temps[i] = 0;
  }

  for (int i = 0; i < 128; i++) {
    scr[i] = 0;
  }

  ekran.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  int deger = analogRead(A0);

  double temp;
  temp = log(((10240000 / deger) - 10000));
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp);
  temp = temp - 273.15;

  temps[temps_i] = temp;
  temps_i = temps_i + 1;

  if (temps_i >= 16) {
    temps_i = 0;

    double avg = 0;

    for (int i = 0; i < 16; i++) {
      avg = avg + temps[i];
    }

    son = avg / 16;
    scr[scr_i] = son * 4;

    scr_i = scr_i + 1;

    if (scr_i >= 128) {
      for (int i = 1; i < 128; i++) {
        scr[i - 1] = scr[i];
      }
      scr_i = 127;
    }
  }

  ekran.clearDisplay();
  ekran.fillRect(0, 0, 128, 9, WHITE);
  ekran.setTextColor(BLACK);
  ekran.setTextSize(1);
  ekran.setCursor(18, 1);
  ekran.print("Sicaklik: ");
  ekran.print(son);

  ekran.setTextColor(WHITE);
  ekran.setCursor(16-4, 12);
  ekran.print(int(scr[16]/4));
  ekran.setCursor(64-4, 12);
  ekran.print(int(scr[64]/4));
  ekran.setCursor(112-4, 12);
  ekran.print(int(scr[112])/4);
  
  for (int i = 0; i < 128; i++) {
    ekran.drawLine(i, (64 - int(scr[i]) + 90)+1, i, (64 - int(scr[i]) + 90), WHITE);
  }

  ekran.display();
  delay(500);
}
