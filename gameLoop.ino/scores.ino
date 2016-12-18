#include "data.h"
#include <string.h>

int checkScore(uint32_t score) {
  EEPROMRead(&read_val, address, size_data);
  /*------Reset EEPROM ADDRESS TO 0-------//
  score = 0;
  store = &score;
  EEPROMProgram(store,address,size_data);
  EEPROMRead(&read_val, address, size_data);
  Serial.print("val ");
  Serial.println(int(read_val)); 
  //---------------*/
  if ((int)read_val < score) {
    //score = 0;
    store = &score;
    EEPROMProgram(store,address,size_data); 
    highscore = score;
  } else {
    Serial.print("val ");
    Serial.println(int(read_val));
    highscore = (int)read_val;
  }
}

void printScore(uint32_t k, int X1, int Y1){
  int scr;
  OrbitOledMoveTo(X1,Y1);
  char digitArray[10] = {0};
  scr = (int)k;
  
  for(int j = 0; j<10&&scr!=0;j++){
    digitArray[j] = scr%10;
    scr/=10;
  }
  int flag2 = 0;
  for(int j =10; j>=0;j--){
    //Serial.println((int)digitArray[j]);
    if(!flag2){
      if(digitArray[j] != 0){
        
        OrbitOledDrawChar(digitArray[j] + 48);
        flag2 = 1;
      }
      continue;
    }
    X1+=6;
    OrbitOledMoveTo(X1,Y1);
    OrbitOledDrawChar(digitArray[j] +48);
  }
  if(!flag2){
    OrbitOledDrawChar('0');
  }
}

