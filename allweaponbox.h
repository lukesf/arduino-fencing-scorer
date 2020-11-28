#ifndef _ALLWEAPONBOX_
#define _ALLWEAPONBOX_
#include <Arduino.h>


//=================
// mode constants
//=================

enum WEAPON {FOIL, EPEE, SABRE, NUM_WEAPONS};
const String WEAPON_TXT[] = {"Foil", "Epee", "Sabre", "NoWeapon"};


class Blade {
  public:
 	Blade(void) {};
  	~Blade() {};
  	int ground = 0;
  	int weapon = 0;
  	int lame = 0;
};

class Adafruit_NeoMatrix;

class AllWeaponBox {

  public:
 	AllWeaponBox(Adafruit_NeoMatrix *arg_leds): leds(arg_leds) { };
  	~AllWeaponBox() {};

	void setup(Stream *out = NULL, int arg_beep = -1);
    void loop(const Blade &a, const Blade &b);

  
	WEAPON weapon = EPEE;

  	void setWeapon(const WEAPON weapon);
	const String getWeaponName();
  	void resetGame();
  	void toggleBeep () { if (beep_pin >=0) beep_on = !beep_on; }

  private:
  	void foil(const Blade &a, const Blade &b);
  	void epee(const Blade &a, const Blade &b);
  	void sabre(const Blade &a, const Blade &b);
  	void signalHits(const Blade &a, const Blade &b);
  	void resetValues();
  	void showScore();

  	Stream * out;
  	Adafruit_NeoMatrix *leds;
  	int beep_pin;
  	boolean beep_on = false;
	//=======================
	// depress and timeouts
	//=======================
	long depressAtime = 0;
	long depressBtime = 0;
	bool lockedOut    = false;
	int scoreA =0;
    int scoreB =0;


	//=========
	// states
	//=========
	boolean depressedA  = false;
	boolean depressedB  = false;
	boolean hitOnTargA  = false;
	boolean hitOffTargA = false;
	boolean hitOnTargB  = false;
	boolean hitOffTargB = false;
};

#endif