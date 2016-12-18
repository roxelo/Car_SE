#ifndef ACCEL_H
#define ACCEL_H

  
void WireRequestArray(int address, uint8_t* buffer, uint8_t amount);
void WireWriteRegister(int address, uint8_t reg, uint8_t value);
void WireWriteByte(int address, uint8_t value);

uint16_t xi;
uint16_t yi;
uint16_t zi;
float x;
float y;
float z;
int shake_difficulty = 30;

//--------gyro variables---------//
int gyro_correct= 0; // 151
float gyro_reading = 0;
int i = 0; 
//------------------------------*/

int check = 0;

//--------LED SHAKE------------//
#define LED RED_LED
int when;
int time_shake = -1;
int shake = 0;
int count_s = 0;

//------------------------------*/

#endif
