#include <DigiUSB.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define STRIPSIZE 60
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  //DigiUSB.begin();
  //DigiUSB.println("Waiting for keyboard input...");
  strip.begin();
  strip.setBrightness(15);  // Lower brightness and save eyeballs!
  strip.show(); // Initialize all pixels to 'off'
}

void get_input2() {
  return;
  int lastRead = -1;
  // when there are characters to read, or the character is a newline
  while (DigiUSB.available() and lastRead != '\n') {
    // something to read
    lastRead = DigiUSB.read();
    DigiUSB.write(lastRead);
  }
    
  // refresh the usb port for 10 milliseconds
  DigiUSB.delay(10);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  get_input2(); colorWipe(strip.Color(0,0,0), 25); // Black
  get_input2(); colorWipe(strip.Color(64, 0, 0), 100); // Red
  get_input2(); colorWipe(strip.Color(0, 64, 0), 100); // Green
  get_input2(); colorWipe(strip.Color(0, 0, 64), 100); // Blue
  get_input2(); colorWave(75);
  get_input2(); colorWipe(strip.Color(0,0,0), 100); // Black
  get_input2(); rainbow(15);
  get_input2(); colorWipe(strip.Color(0,0,0), 100); // Black
  //get_input2(); rainbowCycle(15);
  //get_input2(); colorWipe(strip.Color(0,0,0), 100); // Black
  //get_input2(); colorWave(30);
}
 
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
 
/**
 *      ^   ^   ^  
 * ~~~~~ ColorWave ~~~~~
 *        V   V   V   
 */
void colorWave(uint8_t wait) {
  int i, j, stripsize, cycle;
  float ang, rsin, gsin, bsin, offset;
 
  static int tick = 0;
  
  stripsize = strip.numPixels();
  cycle = stripsize * 25; // times around the circle...
 
  while (++tick % cycle) {
    offset = map2PI(tick);
 
    for (i = 0; i < stripsize; i++) {
      ang = map2PI(i) - offset;
      rsin = sin(ang);
      gsin = sin(2.0 * ang / 3.0 + map2PI(int(stripsize/6)));
      bsin = sin(4.0 * ang / 5.0 + map2PI(int(stripsize/3)));
      strip.setPixelColor(i, strip.Color(trigScale(rsin), trigScale(gsin), trigScale(bsin)));
    }
 
    strip.show();
    delay(wait);
  }
 
}
 
/**
 * Scale a value returned from a trig function to a byte value.
 * [-1, +1] -> [0, 254] 
 * Note that we ignore the possible value of 255, for efficiency,
 * and because nobody will be able to differentiate between the
 * brightness levels of 254 and 255.
 */
byte trigScale(float val) {
  val += 1.0; // move range to [0.0, 2.0]
  val *= 127.0; // move range to [0.0, 254.0]
 
  return int(val) & 255;
}
 
/**
 * Map an integer so that [0, striplength] -> [0, 2PI]
 */
float map2PI(int i) {
  return PI*2.0*float(i) / float(strip.numPixels());
}

