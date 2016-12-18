//------Wire Setup for Tiva C------//
  //VCC to 3.3V
  //GND to GND
  //SCL to PA6 (SCL pin on Tiva C)
  //SDA to PA7 (SDA pin on Tiva C)
  //INT to PA5
//-------------------------------//

#include <delay.h>
#include <stdbool.h>
#include <string.h>
#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <Wire.h>
#include "object.h";
#include "accel.h";
#include "data.h"
#include <I2Cdev.h>
#include <helper_3dmath.h>
#include <MPU6050.h>
#include <hw_eeprom.h>
#include <eeprom.h>


void WireInit();

const uint32_t Potentiometer = PE_3;
double gameSpeed = 40000;//larger is slower
int counter = 0;



//------button variables--------//
const int b1 = PUSH1; //Bottom-Left button
const int b2 = PUSH2; //Bottom-Right button
const int up = PE_0;
const int down = PD_2;
//------------------------------//

void setup() {
  
  // put your setup code here, to run once:
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  Serial.begin(9600);
  
  WireInit();
  EEPROMInit();
  delay(100);
  GameUIInit();
  srand((7+analogRead(Potentiometer)) * 347);
  randomSeed(analogRead(0));

  Wire.begin();
  pinMode(LED, OUTPUT);

   accel_init();
   
  when = random(10000,15000);
  Serial.println(when);


}

void loop() {
  //i++;
  //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  // put your main code here, to run repeatedly: 
  
  gameLoop();
 
 //getData();
 //tilt();
 //shake_f();

}
