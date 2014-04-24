#include <DigisparkRGB.h>

// the setup routine runs once when you press reset:
void setup()  { 
  DigisparkRGBBegin();
} 


void loop ()
{
  randm_fade();
}

void randm_fade() {
  byte RED = 2;
  byte BLUE = 0;
  byte GREEN = 1;
  
  int r=0,g=0,b=0;
  int R=127,G=127,B=127;
  int Rold,Gold,Bold;
  int FADE_DELAY=25;

  while(1) {
    //Determine new values and save current one.
    Rold=R; Gold=G; Bold=B;
    R=(int)(rand()*255);G=(int)(rand()*255);B=(int)(rand()*255);
    
    //Fade from current to new values
    r=Rold;g=Gold;b=Bold;
    while (r!=R && g!=G && b!=B) {
      DigisparkRGB(RED, r);
      DigisparkRGB(GREEN, g);
      DigisparkRGB(BLUE, b);
      DigisparkRGBDelay(FADE_DELAY);
      if (r!=R) r+=(Rold<R)?+1:-1;
      if (g!=G) g+=(Gold<G)?+1:-1;
      if (b!=B) b+=(Bold<B)?+1:-1;
    }
    
    DigisparkRGBDelay(3000-R-G-B); //change wait delay to try to get better random sequence
  }
}

