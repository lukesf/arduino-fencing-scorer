/*
Author: Luke Fletcher
          
Circuits+Pins:
        Led leds:
          NeoPix Pin 3 GRB - 
        buttons (as digital):
          4 = B1 - left
          5 = B2 - down
          6 = B3 - up (rotate)
          7 = B4 - right
        output (as digital):
          10 = beep?
          
        analog (as ):
          A0 = W1G PullDown
          A1 = W2G PullDown
          A2 = W1T PullDown
          A3 = W2T PullDown
          A4 = W1  Pullup
          A5 = W2  Pullup

Comment:
        Combined Fencing scorer game box.
*/

#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <EasyButton.h>

#include <millisDelay.h>
#include <loopTimer.h>
#include "tetris-neopix.h"
#include "allweaponbox.h"
#include "neopix-box.h"


// NEOPIX BOX WIRING CONSTANTS
#define NEOPIX_PIN 3
#define BUTT1_PIN 7
#define BUTT2_PIN 6
#define BUTT3_PIN 5
#define BUTT4_PIN 4
#define BEEP_PIN 10
#define GND_A_PIN A0
#define LAME_A_PIN A1
#define WEAPON_A_PIN A4
#define GND_B_PIN A2
#define LAME_B_PIN A3
#define WEAPON_B_PIN A5

#define BAUDRATE 115200


// Max is 255, 32 is a conservative value to not overload
// a USB power supply (500mA) for 12x12 pixels.
#define BRIGHTNESS 16

// leds DECLARATION:
// Define full leds width and height.
#define mw 16
#define mh 8
Adafruit_NeoMatrix *leds = new Adafruit_NeoMatrix(8, mh, 
  mw/8, 1, 
  NEOPIX_PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE + 
  NEO_TILE_TOP + NEO_TILE_LEFT +  NEO_TILE_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800 );

// Instance of the button.
EasyButton butt1(BUTT1_PIN);
EasyButton butt2(BUTT2_PIN);
EasyButton butt3(BUTT3_PIN);
EasyButton butt4(BUTT4_PIN);
millisDelay ledsDelay; // the delay object

Blade blade_a;
Blade blade_b;


enum MODE { MODE_FENCING, MODE_TETRIS, NUM_MODES};
const char * MODE_TXT[] = {"Fencing","Tetris","NoMode"};
  
MODE mode = MODE_FENCING;

TetrisNeopix tetris(leds);
AllWeaponBox allweaponbox(leds);
int offset = 0;

void setup() {
  Serial.begin(BAUDRATE);

  leds->begin();
  leds->setTextWrap(false);
  leds->setBrightness(BRIGHTNESS);
  // Test full bright of all LEDs. If brightness is too high
  // for your current limit (i.e. USB), decrease it.
  leds->fillScreen(LED_WHITE_HIGH);
  leds->show();
  delay(500);
  leds->clear();
  leds->show();
  ledsDelay.start(200);

  // setup IO
  pinMode(BEEP_PIN,  OUTPUT);
  // analog inputs for fencing weapons
  pinMode(GND_A_PIN,  INPUT);
  pinMode(WEAPON_A_PIN,  INPUT);
  pinMode(LAME_A_PIN,  INPUT);
  pinMode(GND_B_PIN,  INPUT);
  pinMode(WEAPON_B_PIN,  INPUT);
  pinMode(LAME_B_PIN,  INPUT);

  // setup buttons
  butt1.begin();
  butt2.begin();
  butt3.begin();
  butt4.begin();


  // Setup applications
  butt2.onPressedFor(3000,switchMode);
  //butt1.onPressed(moveLeft);
  //butt4.onPressed(moveRight);


  // tetris.setup();
  // butt1.onPressed([tetris](){ tetris.moveLeft();});
  // butt4.onPressed([tetris](){ tetris.moveRight();});

  allweaponbox.setup(&Serial, BEEP_PIN);
  butt1.onPressed([allweaponbox](){ allweaponbox.setWeapon(FOIL);});
  butt2.onPressed([allweaponbox](){ allweaponbox.setWeapon(EPEE);});
  butt3.onPressed([allweaponbox](){ allweaponbox.setWeapon(SABRE);});
  butt4.onPressed([allweaponbox](){ allweaponbox.resetGame();});
  butt1.onPressedFor(1000,[allweaponbox](){ allweaponbox.toggleBeep();});
  
}

void loop() {
  loopTimer.check(&Serial);
  
  // buttons
  butt1.read();
  butt2.read();
  butt3.read();
  butt4.read();
  //
  blade_a.weapon = analogRead(WEAPON_A_PIN);
  blade_b.weapon = analogRead(WEAPON_B_PIN);
  blade_a.lame   = analogRead(LAME_A_PIN);
  blade_b.lame   = analogRead(LAME_B_PIN);
  blade_a.ground = analogRead(GND_A_PIN);
  blade_b.ground = analogRead(GND_B_PIN);

  // tetris.loop();
  allweaponbox.loop(blade_a, blade_b);

  // redraw
  
  //display_drawText(offset, MODE_TXT[mode]);

  // refresh
  if (ledsDelay.justFinished()) {
    ledsDelay.repeat(); // for next print
    leds->show();
  }
}

// Callback function to be called when the button is pressed.
void switchMode()
{
  mode = mode + 1;
  if (mode == NUM_MODES) {
    mode = 0;
  }
  String txt = "switchMode(" + String(MODE_TXT[mode]) + ")";
  String txt2 = MODE_TXT[mode];
  Serial.println(txt);
  display_scrollText(MODE_TXT[mode]);
}

void display_scrollText(String txt) {
  uint8_t size = max(int(mw/8), 1);
  leds->clear();
  leds->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  leds->setTextSize(1);
  leds->setRotation(0);
  int len = txt.length() *6;
  for (int8_t x=7; x>=-len; x--) {
    leds->clear();
    leds->setCursor(x,0);
    leds->setTextColor(LED_GREEN_HIGH);
    leds->print(txt);
    leds->show();
    delay(100);
  }
}

void display_drawText(int x, String txt) {
  leds->clear();
  leds->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  leds->setTextSize(1);
  leds->setRotation(0);
  leds->clear();
  leds->setCursor(x,0);
  leds->setTextColor(LED_GREEN_HIGH);
  leds->print(txt);
}
