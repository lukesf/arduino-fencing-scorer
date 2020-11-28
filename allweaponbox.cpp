//===========================================================================//
//                                                                           //
//  Desc:    Arduino Code to implement a fencing scoring apparatus           //
//  Dev:     Wnew                                                            //
//  Date:    Nov  2012                                                       //
//  Updated: Sept 2015                                                       //
//  Notes:   1. Basis of algorithm from digitalwestie on github. Thanks Mate //
//           2. Used uint8_t instead of int where possible to optimise       //
//           3. Set ADC prescaler to 16 faster ADC reads                     //
//                                                                           //
//  To do:   1. Could use shift reg on lights and mode LEDs to save pins     //
//           2. Implement short circuit LEDs (already provision for it)      //
//           3. Set up debug levels correctly                                //
// Original Source:                                                          //
//   https://github.com/wnew/fencing_scoring_box                             //
//===========================================================================//

#include "allweaponbox.h"
#include "neopix-box.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>



//============
// #defines
//============
//TODO: set up debug levels correctly
#define DEBUG 1
//#define TEST_LIGHTS       // turns on lights for a second on start up
//#define TEST_ADC_SPEED    // used to test sample rate of ADCs
//#define REPORT_TIMING     // prints timings over serial interface
#define BUZZERTIME  1000  // length of time the buzzer is kept on after a hit (ms)
#define LIGHTTIME   3000  // length of time the lights are kept on after a hit (ms)
#define BEEP_PIN 10

//==========================
// Lockout & Depress Times
//==========================
// the lockout time between hits for foil is 300ms +/-25ms
// the minimum amount of time the tip needs to be depressed for foil 14ms +/-1ms
// the lockout time between hits for epee is 45ms +/-5ms (40ms -> 50ms)
// the minimum amount of time the tip needs to be depressed for epee 2ms
// the lockout time between hits for sabre is 170ms +/-10ms
// the minimum amount of time the tip needs to be depressed (in contact) for sabre 0.1ms -> 1ms
// These values are stored as micro seconds for more accuracy
//                         foil   epee   sabre
const long lockout [] = {300000,  45000, 170000};  // the lockout time between hits
const long depress [] = { 14000,   2000,   1000};  // the minimum amount of time the tip needs to be depressed


//================
// Configuration
//================
void AllWeaponBox::setup(Stream *arg_out, int arg_beep)
{
  out = arg_out;
  beep_pin = arg_beep;
  if (out) {
    out->println("3 Weapon Scoring Box");
    out->println("====================");
    out->print  ("Weapon: ");
    out->println(WEAPON_TXT[weapon]);
  }
  resetValues();
}

//============
// Main Loop
//============
void AllWeaponBox::loop(const Blade &a, const Blade &b)
{
  if (weapon == FOIL)
    foil(a, b);
  else if (weapon == EPEE)
    epee(a, b);
  else if (weapon == SABRE)
    sabre(a, b);
  signalHits(a, b);

}

//=====================
// Mode pin interrupt
//=====================
static void AllWeaponBox::setWeapon(const WEAPON arg) {
  weapon = arg;
  resetGame();
}


//===================
// Main foil method
//===================
void AllWeaponBox::foil(const Blade &a, const Blade &b) {

   long now = micros();
   if (((hitOnTargA || hitOffTargA) && (depressAtime + lockout[0] < now)) || 
       ((hitOnTargB || hitOffTargB) && (depressBtime + lockout[0] < now))) {
      lockedOut = true;
   }

   // weapon A
   if (hitOnTargA == false && hitOffTargA == false) { // ignore if A has already hit
      // off target
      if (900 < a.weapon && b.lame < 100) {
         if (!depressedA) {
            depressAtime = micros();
            depressedA   = true;
         } else {
            if (depressAtime + depress[0] <= micros()) {
               hitOffTargA = true;
            }
         }
      } else {
      // on target
         if (400 < a.weapon && a.weapon < 600 && 400 < b.lame && b.lame < 600) {
            if (!depressedA) {
               depressAtime = micros();
               depressedA   = true;
            } else {
               if (depressAtime + depress[0] <= micros()) {
                  hitOnTargA = true;
               }
            }
         } else {
            // reset these values if the depress time is short.
            depressAtime = 0;
            depressedA   = 0;
         }
      }
   }

   // weapon B
   if (hitOnTargB == false && hitOffTargB == false) { // ignore if B has already hit
      // off target
      if (900 < b.weapon && a.lame < 100) {
         if (!depressedB) {
            depressBtime = micros();
            depressedB   = true;
         } else {
            if (depressBtime + depress[0] <= micros()) {
               hitOffTargB = true;
            }
         }
      } else {
      // on target
         if (400 < b.weapon && b.weapon < 600 && 400 < a.lame && a.lame < 600) {
            if (!depressedB) {
               depressBtime = micros();
               depressedB   = true;
            } else {
               if (depressBtime + depress[0] <= micros()) {
                  hitOnTargB = true;
               }
            }
         } else {
            // reset these values if the depress time is short.
            depressBtime = 0;
            depressedB   = 0;
         }
      }
   }
}


//===================
// Main epee method
//===================
void AllWeaponBox::epee(const Blade &a, const Blade &b) {
   long now = micros();
   if ((hitOnTargA && (depressAtime + lockout[1] < now)) || (hitOnTargB && (depressBtime + lockout[1] < now))) {
      lockedOut = true;
   }

   // weapon A
   //  no hit for A yet    && weapon depress    && opponent lame touched
   if (hitOnTargA == false) {
      if (a.lame > 300 && b.ground < 300) {
         if (!depressedA) {
            depressAtime = micros();
            depressedA   = true;
         } else {
            if (depressAtime + depress[1] <= micros()) {
               hitOnTargA = true;
            }
         }
      } else {
         // reset these values if the depress time is short.
         if (depressedA == true) {
            depressAtime = 0;
            depressedA   = 0;
         }
      }
   }

   // weapon B
   //  no hit for B yet    && weapon depress    && opponent lame touched
   if (hitOnTargB == false) {
      if (b.lame > 300 && a.ground < 300) {
         if (!depressedB) {
            depressBtime = micros();
            depressedB   = true;
         } else {
            if (depressBtime + depress[1] <= micros()) {
               hitOnTargB = true;
            }
         }
      } else {
         // reset these values if the depress time is short.
         if (depressedB == true) {
            depressBtime = 0;
            depressedB   = 0;
         }
      }
   }
}


//===================
// Main sabre method
//===================
void AllWeaponBox::sabre(const Blade &a, const Blade &b) {

   long now = micros();
   if (((hitOnTargA || hitOffTargA) && (depressAtime + lockout[2] < now)) || 
       ((hitOnTargB || hitOffTargB) && (depressBtime + lockout[2] < now))) {
      lockedOut = true;
   }

   // weapon A
   if (hitOnTargA == false && hitOffTargA == false) { // ignore if A has already hit
      // on target
      if (400 < a.weapon && a.weapon < 600 && 400 < b.lame && b.lame < 600) {
         if (!depressedA) {
            depressAtime = micros();
            depressedA   = true;
         } else {
            if (depressAtime + depress[2] <= micros()) {
               hitOnTargA = true;
            }
         }
      } else {
         // reset these values if the depress time is short.
         depressAtime = 0;
         depressedA   = 0;
      }
   }

   // weapon B
   if (hitOnTargB == false && hitOffTargB == false) { // ignore if B has already hit
      // on target
      if (400 < b.weapon && b.weapon < 600 && 400 < a.lame && a.lame < 600) {
         if (!depressedB) {
            depressBtime = micros();
            depressedB   = true;
         } else {
            if (depressBtime + depress[2] <= micros()) {
               hitOnTargB = true;
            }
         }
      } else {
         // reset these values if the depress time is short.
         depressBtime = 0;
         depressedB   = 0;
      }
   }
}


//==============
// Signal Hits
//==============
void AllWeaponBox::signalHits(const Blade &a, const Blade &b) {

  // non time critical, this is run after a hit has been detected
  if (lockedOut) {
#ifdef DEBUG
  // read analog pins  
  out->print(" A.gnd: "); out->print(a.ground); out->print(" A.wea: ");  out->print(a.weapon);
  out->print(" A.lame: "); out->println(a.lame);
  out->print(" B.gnd: "); out->print(b.ground); out->print(" B.wea: "); out->print(b.weapon);
  out->print(" B.lame: "); out->println(b.lame);
  out->print(" A: hitOn:"); out->print(hitOnTargA); out->print(" A: hitOff:"); out->println(hitOffTargA);
  out->print(" B: hitOn:"); out->print(hitOnTargB); out->print(" B: hitOff:"); out->println(hitOffTargB);
  out->print(" A: Score:"); out->print(scoreA); out->print(" B: Score:"); out->println(scoreB);
  out->print(" LockedOut: "); out->println(lockedOut);
#endif
    // Beep?
    if (beep_on)
      digitalWrite(BEEP_PIN,  HIGH);

    // Fill the screen with multiple levels of white to gauge the quality
    leds->clear();
    if (hitOnTargA) {
      leds->fillRect(0,0, 8,8, LED_RED_HIGH);
      scoreA +=1;
    }
    if (hitOnTargB) {
      leds->fillRect(8,0, 8,8, LED_GREEN_HIGH);
      scoreB +=1;
    }
    leds->show();

    resetValues();
  }
}


void AllWeaponBox::resetGame() {
  scoreA = 0; 
  scoreB = 0;
  resetValues();
};


//======================
// Reset all variables
//======================
void AllWeaponBox::resetValues() {
  if (beep_on) {
    delay(BUZZERTIME);             // wait before turning off the buzzer
    digitalWrite(BEEP_PIN,  LOW);
  }
  delay(LIGHTTIME-BUZZERTIME);   // wait before turning off the lights
  leds->clear();
  leds->show();
  showScore();

  lockedOut    = false;
  depressAtime = 0;
  depressedA   = false;
  depressBtime = 0;
  depressedB   = false;

  hitOnTargA  = false;
  hitOffTargA = false;
  hitOnTargB  = false;
  hitOffTargB = false;
  delay(100);
}


//======================
// Reset all variables
//======================
void AllWeaponBox::showScore() {

  leds->clear();
  leds->setTextWrap(false);  // we don't wrap text so it scrolls nicely
  leds->setTextSize(1);
  leds->setRotation(0);
  if (scoreA>scoreB)
    leds->setTextColor(LED_WHITE_HIGH);
  else 
    leds->setTextColor(LED_BLUE_MEDIUM);
  leds->setCursor(2,0);
  leds->print(scoreA);
  if (scoreB>scoreA)
    leds->setTextColor(LED_WHITE_HIGH);
  else 
    leds->setTextColor(LED_BLUE_MEDIUM);
  leds->setCursor(10,0);
  leds->print(scoreB);
  leds->show();

   delay(LIGHTTIME-BUZZERTIME);   // wait before turning off the lights
   leds->clear();
   leds->show();


   delay(100);
}
