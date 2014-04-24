#include <WS2812.h>

int MIN_INTENSITY=3;
int MAX_INTENSITY=10;
int MAX_LED=60;
int i=0, j=1, k=MIN_INTENSITY, l=1;
cRGB value;

WS2812 LED(MAX_LED);

void setup() {
        LED.setOutput(3);
}

void loop() {
  value.r=random(0,k);value.g=random(0,k);value.b=random(0,k);
  LED.set_crgb_at(i, value);

  //LED.sync();
  //delay(10);
  
  i += j;
  if (i > MAX_LED-1) {
    j=-1;
    LED.sync();
    delay(500);
  }
  if (i < 0) {
    j=1;
    k += l;
    if (k > MAX_INTENSITY) l=-1;
    if (k < MIN_INTENSITY) l=1;
    LED.sync();
    delay(500);
  }
}

