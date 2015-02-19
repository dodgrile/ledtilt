#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN        6
#define NUMPIXELS  24


int tilt_s1 = 2;
int tilt_s2 = 3;
int delayVal = 10;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
 pinMode(tilt_s1, INPUT);
 pinMode(tilt_s2, INPUT);
 pixels.begin();
 Serial.begin(9600);
}

void loop(){
  int position = getTiltPosition();
  
  switch (position) {
    case 0:
      setRing(0,0,255);
      break ;
    case 1:
      setRing(0,255,0);
      break ;
    case 2:
      setRing(255,0,0);
      break ;
    case 3:
      setRing(255,255,255);
      break ;
  }
  
  Serial.println(position);
  delay(200); //only here to slow down the serial output
  
  turnoff();
}

int getTiltPosition(){
   int s1 = digitalRead(tilt_s1);
   int s2 = digitalRead(tilt_s2);
   return (s1 << 1) | s2; //bitwise math to combine the values
}

void setRing(int rVal, int gVal, int bVal) {
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(rVal, gVal, bVal)); 

    pixels.show(); 

    delay(delayVal); 

  } 
}


void turnoff() {
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // 0,0,0 turns the pixel off 

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayVal); // Delay for a period of time (in milliseconds).

  } 
}


