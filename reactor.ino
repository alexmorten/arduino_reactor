#include <Adafruit_NeoPixel.h>
 
#define PIN 2
#define N_LEDS 12


#define BIG_N_LEDS 24
#define BIG_DATA_PIN 3

 

Adafruit_NeoPixel big_strip = Adafruit_NeoPixel(BIG_N_LEDS, BIG_DATA_PIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  big_strip.begin();
  
    for (uint16_t i=0; i < BIG_N_LEDS; i++) {
      big_strip.setPixelColor(i, strip.Color(0, 0 , 0));
      strip.setPixelColor(i, strip.Color(0, 0 , 0));
    }
 
 
  big_strip.show();
}
  
int c = 0;
int big_random_delay = 100;
int small_random_delay = 200;
void loop() {

  bigStripColor();
  smallStripColor();
  
  if (c%big_random_delay == 0){
    big_random_LED();
    big_random_delay = random(10, 1200);
  }

 if (c%small_random_delay == 0){
    small_random_LED();
    small_random_delay = random(10, 1800);
  }



  big_strip.show();
  strip.show();
  delay(16);
  c++;
}


void bigStripColor() {
  int cur = c%BIG_N_LEDS;
  for (int i=0; i< big_strip.numPixels(); i++){
    int d = min(abs(cur-i), min(abs(cur - (i+24)), abs(cur - (i-24))));
    big_strip.setPixelColor(i, big_strip.Color(0,0, 50-d*2));
  }
}

void smallStripColor() {
  int cur = c%180;
  float angle_rad = cur * M_PI / 90;
  float res = (cos(angle_rad) + 1) / 2;

  int red = 15 + res*100;
  for (int i=0; i< strip.numPixels(); i++){
    strip.setPixelColor(i, strip.Color(red, 0, 0));
  }
  
}

static void big_random_LED(){
  int p = random(0, big_strip.numPixels());
  int red = random(60,120);
  int green = random(60,120);
  int blue = random(60,120);
  big_strip.setPixelColor(p, big_strip.Color(red, green , blue));
}
 
static void small_random_LED(){
  int p = random(0, strip.numPixels());
  int red = random(60,120);
  int green = random(60,120);
  int blue = random(60,120);
  strip.setPixelColor(p, strip.Color(red, green , blue));
}
