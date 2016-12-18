#include <Wire.h>
#include "accel.h"

static float const    SensorMaximumReading= 512.0;
static float const    SensorMaximumAccel  = 9.81 * 4.0;
static uint8_t const  SensorAccelerometer = 0x1D;
static uint32_t const ShakeThreshold      = 16;
static float          ShakeAccumulator    = 0;

void accel_init()
{ 
  WireWriteRegister(SensorAccelerometer, 0x31, 1);
  WireWriteRegister(SensorAccelerometer, 0x2D, 1 << 3);
 
}

void getData()
{
  size_t const DataLength = 6;
  uint32_t data[DataLength] = { 0 };

  //Serial.println("loop 1");
  
  WireWriteByte(SensorAccelerometer, 0x32);
  //Serial.println("loop 2");
  WireRequestArray(SensorAccelerometer, data, DataLength);
  //Serial.println("loop works");

  xi = (data[1] << 8) | data[0];
  yi = (data[3] << 8) | data[2];
  zi = (data[5] << 8) | data[4];
  x = *(int16_t*)(&xi) / SensorMaximumReading * SensorMaximumAccel;
  y = *(int16_t*)(&yi) / SensorMaximumReading * SensorMaximumAccel;
  z = *(int16_t*)(&zi) / SensorMaximumReading * SensorMaximumAccel;
  
  ShakeAccumulator = sqrt(x*x + y*y + z*z);
  //Serial.println(x);
}

/*
static TwoWire orbitWire(0);

void WireInit()
{
  orbitWire.begin();
}

void WireWriteByte(int address, uint8_t value)
{
  orbitWire.beginTransmission(address);
  orbitWire.write(value);
  orbitWire.endTransmission();
}

void WireWriteRegister(int address, uint8_t reg, uint8_t value)
{
  orbitWire.beginTransmission(address);
  orbitWire.write(reg);
  orbitWire.write(value);
  orbitWire.endTransmission();
}


void WireRequestArray(int address, uint32_t* buffer, uint8_t amount)
{
  orbitWire.requestFrom(address, amount);
  do 
  {
    while(!orbitWire.available());
    *(buffer++) = orbitWire.read();
  } while(--amount > 0);
}

*/
