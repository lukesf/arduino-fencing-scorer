/*
Original Author: Jae Yeong Bae
        UBC ECE
        jocker.tistory.com       
Date:   Jan.18.2013
File:   Tetris v2
Changelog:
        V3: Luke F: Adapted for Color NeoPix
        v2: displays score at gameover
        
Purpose:
        killing time.. + for fun
          
Circuits+Pins:
        Led Matrix:
          NeoPix Pin 3 GRB - 
        buttons (as digital):
          4 = left
          5 = down
          6 = up (rotate)
          7 = right

Original Comment:
        This is my second Arduino Project. 
        Code may be messy and inefficient.
        References from Arduino Library and datasheets.
*/

#include "tetris-neopix.h"

 
void TetrisNeopix::setup()
{
  pinMode(10, OUTPUT);
}

void TetrisNeopix::loop() 
{
  delay(500);
}


/*
#include <Adafruit_NeoPixel.h>

unsigned char NEOPIX_PIN = 3;
unsigned char LEFT_PIN = 7;
unsigned char DOWN_PIN = 6;
unsigned char UP_PIN = 5;
unsigned char RIGHT_PIN = 4;
unsigned char BEEP_PIN = 10;


#define NUMPIXELS      128 // number of neopixels in Ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIX_PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // timing delay

long delays = 0;
short delay_ = 500;
long bdelay = 0;
short buttondelay = 150;
short btdowndelay = 30;
short btsidedelay = 80;
unsigned char blocktype;
unsigned char blockcolor;
unsigned char blockrotation;

int lines = 0;
unsigned char block[8][18]; //2 extra for rotation
unsigned char pile[8][16];
unsigned char disp[8][16];

unsigned char lib[10][5][7];


enum BUTT { BUTT_NONE, BUTT_LEFT, BUTT_DOWN, BUTT_UP, BUTT_RIGHT};

void setup() {
// Score Digit Bitmap library
lib[0][1][0] = 1;
lib[0][2][0] = 1;
lib[0][3][0] = 1;
lib[0][0][1] = 1;
lib[0][4][1] = 1;
lib[0][3][2] = 1;
lib[0][0][2] = 1;
lib[0][4][2] = 1;
lib[0][2][3] = 1;
lib[0][0][3] = 1;
lib[0][4][3] = 1;
lib[0][1][4] = 1;
lib[0][0][4] = 1;
lib[0][4][4] = 1;
lib[0][0][5] = 1;
lib[0][4][5] = 1;
lib[0][1][6] = 1;
lib[0][2][6] = 1;
lib[0][3][6] = 1;
lib[1][2][0] = 1;
lib[1][1][1] = 1;
lib[1][2][1] = 1;
lib[1][2][2] = 1;
lib[1][2][3] = 1;
lib[1][2][4] = 1;
lib[1][2][5] = 1;
lib[1][1][6] = 1;
lib[1][2][6] = 1;
lib[1][3][6] = 1;
lib[2][1][0] = 1;
lib[2][2][0] = 1;
lib[2][3][0] = 1;
lib[2][0][1] = 1;
lib[2][4][1] = 1;
lib[2][4][2] = 1;
lib[2][3][3] = 1;
lib[2][2][4] = 1;
lib[2][1][5] = 1;
lib[2][0][6] = 1;
lib[2][1][6] = 1;
lib[2][2][6] = 1;
lib[2][3][6] = 1;
lib[2][4][6] = 1;
lib[3][0][0] = 1;
lib[3][1][0] = 1;
lib[3][2][0] = 1;
lib[3][3][0] = 1;
lib[3][4][0] = 1;
lib[3][3][1] = 1;
lib[3][2][2] = 1;
lib[3][3][3] = 1;
lib[3][4][4] = 1;
lib[3][0][5] = 1;
lib[3][4][5] = 1;
lib[3][1][6] = 1;
lib[3][2][6] = 1;
lib[3][3][6] = 1;
lib[4][3][0] = 1;
lib[4][2][1] = 1;
lib[4][3][1] = 1;
lib[4][1][2] = 1;
lib[4][3][2] = 1;
lib[4][0][3] = 1;
lib[4][3][3] = 1;
lib[4][0][4] = 1;
lib[4][1][4] = 1;
lib[4][2][4] = 1;
lib[4][3][4] = 1;
lib[4][4][4] = 1;
lib[4][3][5] = 1;
lib[4][3][6] = 1;
lib[5][0][0] = 1;
lib[5][1][0] = 1;
lib[5][2][0] = 1;
lib[5][3][0] = 1;
lib[5][4][0] = 1;
lib[5][0][1] = 1;
lib[5][0][2] = 1;
lib[5][1][2] = 1;
lib[5][2][2] = 1;
lib[5][3][2] = 1;
lib[5][4][3] = 1;
lib[5][4][4] = 1;
lib[5][0][5] = 1;
lib[5][4][5] = 1;
lib[5][1][6] = 1;
lib[5][2][6] = 1;
lib[5][3][6] = 1;
lib[6][2][0] = 1;
lib[6][3][0] = 1;
lib[6][1][1] = 1;
lib[6][0][2] = 1;
lib[6][0][3] = 1;
lib[6][1][3] = 1;
lib[6][2][3] = 1;
lib[6][3][3] = 1;
lib[6][0][4] = 1;
lib[6][4][4] = 1;
lib[6][0][5] = 1;
lib[6][4][5] = 1;
lib[6][1][6] = 1;
lib[6][2][6] = 1;
lib[6][3][6] = 1;
lib[7][0][0] = 1;
lib[7][1][0] = 1;
lib[7][2][0] = 1;
lib[7][3][0] = 1;
lib[7][4][0] = 1;
lib[7][4][1] = 1;
lib[7][3][2] = 1;
lib[7][2][3] = 1;
lib[7][1][4] = 1;
lib[7][1][5] = 1;
lib[7][1][6] = 1;
lib[8][1][0] = 1;
lib[8][2][0] = 1;
lib[8][3][0] = 1;
lib[8][0][1] = 1;
lib[8][4][1] = 1;
lib[8][0][2] = 1;
lib[8][4][2] = 1;
lib[8][1][3] = 1;
lib[8][2][3] = 1;
lib[8][3][3] = 1;
lib[8][0][4] = 1;
lib[8][4][4] = 1;
lib[8][0][5] = 1;
lib[8][4][5] = 1;
lib[8][1][6] = 1;
lib[8][2][6] = 1;
lib[8][3][6] = 1;
lib[9][1][0] = 1;
lib[9][2][0] = 1;
lib[9][3][0] = 1;
lib[9][0][1] = 1;
lib[9][4][1] = 1;
lib[9][0][2] = 1;
lib[9][4][2] = 1;
lib[9][1][3] = 1;
lib[9][2][3] = 1;
lib[9][3][3] = 1;
lib[9][4][3] = 1;
lib[9][4][4] = 1;
lib[9][3][5] = 1;
lib[9][1][6] = 1;
lib[9][2][6] = 1;


  int seed = 
  (analogRead(0)+1)*
  (analogRead(1)+1)*
  (analogRead(2)+1)*
  (analogRead(3)+1);
  randomSeed(seed);
  random(10,9610806);
  seed = seed *random(3336,15679912)+analogRead(random(4)) ;
  randomSeed(seed);  
  random(10,98046);  
    
  pinMode(UP_PIN, INPUT_PULLUP); //up
  pinMode(RIGHT_PIN, INPUT_PULLUP); //right
  pinMode(LEFT_PIN, INPUT_PULLUP); //left
  pinMode(DOWN_PIN, INPUT_PULLUP); //down 
  pinMode(BEEP_PIN, OUTPUT); //beep 


  pixels.begin(); // Initializes the NeoPixel library.
  
  newBlock();
  updateLED();    

  Serial.begin(9600);
}

void loop() {
  
  if (delays < millis())
   {
     delays = millis() + delay_;
     movedown();
   }
   
   //buttun actions
  int button = readButt();
  
  if (button == BUTT_UP) //up=rotate
    rotate();
  if (button == BUTT_RIGHT) //right=moveright
    moveright();    
  if (button == BUTT_LEFT) //left=moveleft
    moveleft();
  if (button == BUTT_DOWN) //down=movedown
    movedown();  
  Serial.print(button);
  // digitalWrite(BEEP_PIN,HIGH);
  LEDRefresh();
}

boolean moveleft()
{  
  if (space_left()) {
    for (int i=0;i<7;i++) {
      for (int j=0;j<16;j++) {
        block[i][j]=block[i+1][j];
      }
    }
    
    for (int j=0;j<16;j++) {
      block[7][j]=0;
    }    
    updateLED();
    return 1;
  }
  return 0;
}

boolean moveright()
{
  if (space_right()) {
    for (int i=7;i>0;i--) {
      for (int j=0;j<16;j++) {
        block[i][j]=block[i-1][j];
      }
    }
    for (int j=0;j<16;j++) {
      block[0][j]=0;
    }    
    updateLED(); 
    return 1;   
  }
  return 0;
}

int readButt()
{
  if (bdelay > millis()) {
    return BUTT_NONE;
  }
  if (digitalRead(LEFT_PIN) == LOW) {
    bdelay = millis() + btsidedelay;    
    return BUTT_LEFT;
  }
  if (digitalRead(DOWN_PIN) == LOW) {
    bdelay = millis() + btdowndelay;    
    return BUTT_DOWN;
  }    
  if (digitalRead(RIGHT_PIN) == LOW) {
    bdelay = millis() + btsidedelay;
    // digitalWrite(BEEP_PIN,HIGH);
    return BUTT_RIGHT;
  }
  if (digitalRead(UP_PIN) == LOW) {
    bdelay = millis() + buttondelay;
    return BUTT_UP;
  }  
  return BUTT_NONE;
}

void updateLED()
{
  for (int i=0;i<8;i++) {
    for (int j=0;j<16;j++) {
      disp[i][j] = block[i][j] | pile[i][j];
    }
  }
}

void rotate()
{
  //skip for square block(3)
  if (blocktype == 3) return;

  int xi;
  int yi;
  //detect left
  for (int i=7;i>=0;i--) {
    for (int j=0;j<16;j++) {
      if (block[i][j]) {
        xi = i;
      }
    }
  }  
  //detect up
  for (int i=15;i>=0;i--) {
    for (int j=0;j<8;j++) {
      if (block[j][i]) {
        yi = i;
      }
    }
  } 
  if (blocktype == 0) {
    if (blockrotation == 0) {
      if (!space_left()) {
        if (space_right3()) {
          if (!moveright())
            return;
          xi++;
        }
        else return;
      }     
      else if (!space_right()) {
        if (space_left3()) {
          if (!moveleft())
            return;
          if (!moveleft())
            return;          
          xi--;
          xi--;        
        }
        else
          return;
      }
      else if (!space_right2()) {
        if (space_left2()) {
          if (!moveleft())
            return;          
          xi--;      
        }
        else
          return;
      }   
         
      block[xi][yi]=0;
      block[xi][yi+2]=0;
      block[xi][yi+3]=0;      
      
      block[xi-1][yi+1]=blockcolor;
      block[xi+1][yi+1]=blockcolor;
      block[xi+2][yi+1]=blockcolor;      

      blockrotation = 1;
    }
    else {
      block[xi][yi]=0;
      block[xi+2][yi]=0;
      block[xi+3][yi]=0;
      
      block[xi+1][yi-1]=blockcolor;
      block[xi+1][yi+1]=blockcolor;
      block[xi+1][yi+2]=blockcolor;

      blockrotation = 0;
    }    
  }
  
  //offset to mid
  xi ++;  
  yi ++;  
  
  if (blocktype == 1) {
    if (blockrotation == 0) {
      block[xi-1][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] =blockcolor;
      block[xi+1][yi-1] =blockcolor;
      block[xi][yi+1] =blockcolor;      
      
      blockrotation = 1;
    }
    else if (blockrotation == 1) {
      if (!space_left()) {
        if (!moveright())
          return;
        xi++;
      }        
      xi--;
      
      block[xi][yi-1] = 0;
      block[xi+1][yi-1] = 0;
      block[xi][yi+1] = 0;      
      
      block[xi-1][yi] =blockcolor;
      block[xi+1][yi] =blockcolor;
      block[xi+1][yi+1] =blockcolor;      
      
      blockrotation = 2;      
    }
    else if (blockrotation == 2) {
      yi --;
      
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi+1][yi+1] = 0;      
      
      block[xi][yi-1] =blockcolor;
      block[xi][yi+1] =blockcolor;
      block[xi-1][yi+1] =blockcolor;      
      
      blockrotation = 3;            
    }
    else {
      if (!space_right()) {
        if (!moveleft())
          return;
        xi--;
      }
      block[xi][yi-1] = 0;
      block[xi][yi+1] = 0;
      block[xi-1][yi+1] = 0;        

      block[xi-1][yi-1] =blockcolor;
      block[xi-1][yi] =blockcolor;
      block[xi+1][yi] =blockcolor;
      
      blockrotation = 0;          
    }  
  }

  if (blocktype == 2) {
    if (blockrotation == 0) {
      block[xi+1][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] =blockcolor;
      block[xi+1][yi+1] =blockcolor;
      block[xi][yi+1] =blockcolor;      
      
      blockrotation = 1;
    }
    else if (blockrotation == 1) {
      if (!space_left())
      {
        if (!moveright())
          return;
        xi++;
      }              
      xi--;
      
      block[xi][yi-1] = 0;
      block[xi+1][yi+1] = 0;
      block[xi][yi+1] = 0;      
      
      block[xi-1][yi] =blockcolor;
      block[xi+1][yi] =blockcolor;
      block[xi-1][yi+1] =blockcolor;      
      
      blockrotation = 2;      
    }
    else if (blockrotation == 2) {
      yi --;
      
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi-1][yi+1] = 0;      
      
      block[xi][yi-1] =blockcolor;
      block[xi][yi+1] =blockcolor;
      block[xi-1][yi-1] =blockcolor;      
      
      blockrotation = 3;            
    }
    else {
      if (!space_right())
      {
        if (!moveleft())
          return;
        xi--;
      }      
      block[xi][yi-1] = 0;
      block[xi][yi+1] = 0;
      block[xi-1][yi-1] = 0;        

      block[xi+1][yi-1] =blockcolor;
      block[xi-1][yi] =blockcolor;
      block[xi+1][yi] =blockcolor;
      
      blockrotation = 0;          
    }  
  }
  
  if (blocktype == 4) {
    if (blockrotation == 0) {
      block[xi+1][yi-1] = 0;
      block[xi-1][yi] = 0;

      block[xi+1][yi] =blockcolor;
      block[xi+1][yi+1] =blockcolor;      
      
      blockrotation = 1;
    }
    else {
      if (!space_left()) {
        if (!moveright())
          return;
        xi++;
      }              
      xi--;
      
      block[xi+1][yi] = 0;
      block[xi+1][yi+1] = 0;      
      
      block[xi-1][yi] =blockcolor;
      block[xi+1][yi-1] =blockcolor;
      
      blockrotation = 0;          
    }  
  }  

  if (blocktype == 5) {
    if (blockrotation == 0) {
      block[xi][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;

      block[xi][yi-1] =blockcolor;
      block[xi+1][yi] =blockcolor;
      block[xi][yi+1] =blockcolor;      
      
      blockrotation = 1;
    }
    else if (blockrotation == 1) {
      if (!space_left()) {
        if (!moveright())
          return;
        xi++;
      }              
      xi--;
      
      block[xi][yi-1] = 0;
      block[xi+1][yi] = 0;
      block[xi][yi+1] = 0;
      
      block[xi-1][yi] =blockcolor;
      block[xi+1][yi] =blockcolor;
      block[xi][yi+1] =blockcolor;
      
      blockrotation = 2;      
    }
    else if (blockrotation == 2) {
      yi --;
      
      block[xi-1][yi] = 0;
      block[xi+1][yi] = 0;
      block[xi][yi+1] = 0;     
      
      block[xi][yi-1] =blockcolor;
      block[xi-1][yi] =blockcolor;
      block[xi][yi+1] =blockcolor;      
      
      blockrotation = 3;            
    }
    else {
      if (!space_right()) {
        if (!moveleft())
          return;
        xi--;
      }      
      block[xi][yi-1] = 0;
      block[xi-1][yi] = 0;
      block[xi][yi+1] = 0;      
      
      block[xi][yi-1] =blockcolor;
      block[xi-1][yi] =blockcolor;
      block[xi+1][yi] =blockcolor;
      
      blockrotation = 0;          
    }  
  }
  
  if (blocktype == 6) {
    if (blockrotation == 0) {
      block[xi-1][yi-1] = 0;
      block[xi][yi-1] = 0;

      block[xi+1][yi-1] =blockcolor;
      block[xi][yi+1] =blockcolor;      
      
      blockrotation = 1;
    }
    else {
      if (!space_left()) {
        if (!moveright())
          return;
        xi++;
      }              
      xi--;
      
      block[xi+1][yi-1] = 0;
      block[xi][yi+1] = 0;      
      
      block[xi-1][yi-1] =blockcolor;
      block[xi][yi-1] =blockcolor;
      
      blockrotation = 0;          
    }  
  }  

  //if rotating made block and pile overlap, push rows up
  while (!check_overlap())
  {
    for (int i=0;i<18;i++) {
      for (int j=0;j<8;j++) {
         block[j][i] = block[j][i+1];
      }
    }
    delays = millis() + delay_;
  }
  
  
  updateLED();
}

void movedown()
{
  if (space_below())
  {
    //move down
    for (int i=15;i>=0;i--) {
      for (int j=0;j<8;j++) {
        block[j][i] = block[j][i-1];
      }
    }
    for (int i=0;i<7;i++) {
      block[i][0] = 0;
    }
  }
  else
  {
    //merge and new block
    for (int i=0;i<8;i++) {
     for(int j=0;j<16;j++) {
       if (block[i][j]) {
         pile[i][j]=block[i][j];
         block[i][j]=0;
       }
     }
    }
    newBlock();   
  }
  updateLED();  
}

boolean check_overlap()
{
  for (int i=0;i<16;i++) {
    for (int j=0;j<7;j++) {
       if (block[j][i]) {
         if (pile[j][i])
           return false;
       }
    }
  }
  for (int i=16;i<18;i++) {
    for (int j=0;j<7;j++) {
       if (block[j][i]) {
         return false;
       }        
    }
  }  
  return true;
}

void check_gameover()
{
  int cnt=0;
  for(int i=15;i>=0;i--)
  {
    cnt=0;
    for (int j=0;j<8;j++)
    {
      if (pile[j][i]) {
        cnt ++;
      }
    }    
    if (cnt == 8) {
        lines++;
      for (int j=0;j<8;j++) {
        pile[j][i]=0;
      }
      updateLED();
      LEDRefresh();
      delay(50);
      
      for(int k=i;k>0;k--) {
        for (int j=0;j<8;j++) {
          pile[j][k] = pile[j][k-1];
        }                
      }
      for (int j=0;j<8;j++)
      {
        pile[j][0] = 0;
      }        
      updateLED();
      LEDRefresh();     
      delay(50);      
      i++;     
    }
  }
  
  for(int i=0;i<8;i++)
  {
    if (pile[i][0])
      gameover();
  }
  return;
}

void gameover()
{
  Serial.print("GameOver!");
  //close blind
  for (int i=0;i<8;i++)
  {
     for (int j=0;j<16;j++)
     {
       if (j%2)
       {
         disp[i][j]=1;
       }
       else
       {
         disp[7-i][j]=1;        
       }
     }
     LEDRefresh();
     delay(60);
  }
 
  //calculate score board
  int num_lines;
  num_lines = 2;
  boolean score[8][17];
  for (int i=0;i<8;i++) {
    for (int j=0;j<16;j++) {
      score[i][j] = 0;
    }
  }       
  int digit1 = (lines/10) % 10;
  int digit2 = (lines) % 10;
    
  for (int i=0;i<5;i++) {
    for (int j=0;j<8;j++) {
      score[7-j][i+3]  = lib[digit1][i][j];
    }
  }
  for (int i=0;i<5;i++) {
    for (int j=0;j<8;j++) {
      score[7-j][i+9]  = lib[digit2][i][j];                
    }
  }    
  for (int i=0;i<16;i++) {
    score[0][i]=0;
  }
    
  //open blind with score    
  for (int i=0;i<8;i++) {
    for (int j=0;j<16;j++) {
      if (j%2) {
        disp[i][j]=score[i][j];
      }
      else {
        disp[7-i][j]=score[7-i][j];
      }
    }
    LEDRefresh();     
    delay(60);
  }       
  LEDRefresh();       
  delay(100);    
    
  while(true) {
    for (int i=0;i<8;i++) {
      for (int j=0;j<16;j++) {
        disp[i][j] = score[i][j];
      }
    }   
        
    boolean tmpline[8];
    for (int i=0;i<8;i++) {
      score[i][16]=score[i][0];
    }
        
    for (int i=0;i<8;i++) {
      for (int j=0;j<16;j++) {
        score[i][j] = score[i][j+1];
      }
    }
    LEDRefresh();      
    delay(100);
  }
  
}

void newBlock()
{
  check_gameover();
  
  
  blocktype = random(7);
  blockcolor = random(1,4);
  
  if (blocktype == 0)
  // 0
  // 0
  // 0
  // 0
  {
    block[3][0]=blockcolor;
    block[3][1]=blockcolor;
    block[3][2]=blockcolor;
    block[3][3]=blockcolor;      
  }

  if (blocktype == 1)
  // 0
  // 0 0 0
  {
    block[2][0]=blockcolor;
    block[2][1]=blockcolor;
    block[3][1]=blockcolor;
    block[4][1]=blockcolor;        
  }
  
  if (blocktype == 2)
  //     0
  // 0 0 0
  {
    block[4][0]=blockcolor;
    block[2][1]=blockcolor;
    block[3][1]=blockcolor;
    block[4][1]=blockcolor;         
  }

  if (blocktype == 3)
  // 0 0
  // 0 0
  {
    block[3][0]=blockcolor;
    block[3][1]=blockcolor;
    block[4][0]=blockcolor;
    block[4][1]=blockcolor;          
  }    

  if (blocktype == 4)
  //   0 0
  // 0 0
  {
    block[4][0]=blockcolor;
    block[5][0]=blockcolor;
    block[3][1]=blockcolor;
    block[4][1]=blockcolor;         
  }    
  
  if (blocktype == 5)
  //   0
  // 0 0 0
  {
    block[4][0]=blockcolor;
    block[3][1]=blockcolor;
    block[4][1]=blockcolor;
    block[5][1]=blockcolor;       
  }        

  if (blocktype == 6)
  // 0 0
  //   0 0
  {
    block[3][0]=blockcolor;
    block[4][0]=blockcolor;
    block[4][1]=blockcolor;
    block[5][1]=blockcolor;         
  }    

  blockrotation = 0;
}

boolean space_below()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (i == 15)
           return false;
         if (pile[j][i+1])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_left2()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0 || j == 1)
           return false;
         if (pile[j-1][i] | pile[j-2][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_left3()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0 || j == 1 ||j == 2 )
           return false;
         if (pile[j-1][i] | pile[j-2][i]|pile[j-3][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_left()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 0)
           return false;
         if (pile[j-1][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_right()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7)
           return false;
         if (pile[j+1][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_right3()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7||j == 6||j == 5)
           return false;
         if (pile[j+1][i] |pile[j+2][i] | pile[j+3][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}

boolean space_right2()
{ 
  int i;
  int j;  
  for (i=15;i>=0;i--)
  {
    for (j=0;j<8;j++)
    {
       if (block[j][i])
       {
         if (j == 7 || j == 6)
           return false;
         if (pile[j+1][i] |pile[j+2][i])
         {
           return false;
         }      
       }        
    }
  }
  return true;
}


void LEDRefresh()
{
    unsigned char color = 0;
    for (int j=0;j<16;j++) {
      for (int i=0;i<8;i++) {
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        if (disp[7-i][15-j]) {
          switch (disp[7-i][15-j]) {
            case 1:
              pixels.setPixelColor(i+j*8, pixels.Color(10, 0, 0)); // Red color.
            break;
            case 2:
              pixels.setPixelColor(i+j*8, pixels.Color(0, 10, 0)); // Green color.
            break;
            case 3:
              pixels.setPixelColor(i+j*8, pixels.Color(0, 0, 10)); // Blue color.
            break;
          }
        }
        else {
          pixels.setPixelColor(i+j*8, pixels.Color(0, 0, 0)); // Off.
        }
        pixels.show(); // This sends the updated pixel color to the hardware.
        // delay(delayval); // Delay for a period of time (in milliseconds).        
      }
    }     
}
*/
