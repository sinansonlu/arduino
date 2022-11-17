#include <TM1638.h>

#define STB 10
#define CLK 9
#define DIO 8

#define BUZZ 7

TM1638 tm(CLK, DIO, STB);

void setup() {
  Serial.begin(9600);
  tm.reset();
  pinMode(BUZZ, OUTPUT);
}

int tutulanSure = 5000;
unsigned long sure = millis();
unsigned long toplamSure = sure + tutulanSure;
int kalanSure = (toplamSure - sure) / 1000;

const uint8_t text[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };

void loop() {
  uint8_t buttons = tm.getButtons();
  
  if (kalanSure >= 0) {
    tm.writeLeds(0b00000000);
    sure = millis();
    kalanSure = (toplamSure - sure) / 1000;
    int tmp = kalanSure;
    for (int i = 0; i < 8; i++) {
      tm.displayDig(i, text[(tmp % 10)]);
      tmp = tmp / 10;
    }
    noTone(BUZZ);
  } else {
    tm.writeLeds(random(0, 256));
    int tmp = 0;
    for (int i = 0; i < 8; i++) {
      tm.displayDig(i, text[(tmp % 10)]);
      tmp = tmp / 10;
    }
    tone(BUZZ, random(30, 500));
  }

  if (buttons == 1) {
    toplamSure = sure + tutulanSure;
    kalanSure = (toplamSure - sure) / 1000;
  }
}
