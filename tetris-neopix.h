#ifndef _TETRIS_NEOPIX_
#define _TETRIS_NEOPIX_
#include <Arduino.h>

class Adafruit_NeoMatrix;

class TetrisNeopix {

 public:
 	TetrisNeopix(Adafruit_NeoMatrix *arg): leds(arg) {};
  	~TetrisNeopix() {};

	void setup();
    void loop();
 private:
	 Adafruit_NeoMatrix	*leds;
};
#endif
