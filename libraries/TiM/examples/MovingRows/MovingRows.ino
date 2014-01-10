#include "TiM.h"
#include <Adafruit_NeoPixel.h>

TiM tim;

int clr=0;  // Just a toggle variable
int nw=0;  // Counter for iterating through the rows

// Use Arduino Pins for controling the rows of TiM
uint8_t pins[8] = {
  2, 3, 4, 5, 8, 9,10,11};

const uint16_t n_led_per_row = 16;

const uint8_t N_ROW = 8;
const uint8_t N_COL = 16;
const uint8_t BRIGHT = 205;

void setup() {
  Serial.begin(9600);
  tim.setup(8, n_led_per_row, pins);

  for(int i=0;i<N_ROW;i++) {
    for (int j=0;j<N_COL;j++) {
      tim.setPixel(i,j,Color(0,120,120));
      tim.show();
      delay(50);
      tim.setPixel(i,j,Color(0,0,0));
      tim.show();
    }
  }

  for(int i=0;i<N_COL;i++) {
    tim.setPixel(0,i,Color(20+i*10,255-i*10,0));
    tim.show();
    delay(50);
  }
  delay(500);
}

void loop() {

  while(!clr) {
    shiftRowDown();
    tim.show();
    ++nw;
    if(nw==7) clr=1;
    delay(500);
  }

  while(clr) {

    shiftRowUp();
    tim.show();
    --nw;
    if(nw<1) {
      clr=0;
    }
    delay(500);
  }

  while(!clr) {

    tim.copyRow(nw+1,nw);
    tim.show();
    ++nw;
    if(nw==7) clr=1;
    delay(500);
  }

  while(clr) {
    tim.clearRow(nw);
    tim.show();
    --nw;
    if(nw<1) {
      clr=0;
    }
    delay(500);
  }
}

void shiftRowDown() {
  for(int i=N_ROW-2;i>=0;--i) {
    tim.copyRow(i+1,i);
  }
  tim.clearRow(0);
}

void shiftRowUp() {
  Serial.println("isru");
  for(int i=0;i<=N_ROW-2;++i) {
    tim.copyRow(i,i+1);
  }
  tim.clearRow(N_ROW-1);
}






