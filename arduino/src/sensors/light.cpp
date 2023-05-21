# include "light.h"

# include <Arduino.h>
# include <Wire.h>

# define DEFAULT_ADDR 0x23

LightSensor::LightSensor()
{
    LightSensor(DEFAULT_ADDR);
}

LightSensor::LightSensor(int addr)
{
    setSensorType(LIGHT);
    setInputPin(A4);

    setAddr(addr);
}

void LightSensor::begin()
{
    Wire.begin();
    sensor.begin();
}

float LightSensor::readFloatInput()
{
    return sensor.readLightLevel();
}

long LightSensor::readInput()
{
    return (long) readFloatInput();
}

void LightSensor::setAddr(int _addr) { addr = _addr; }
int LightSensor::getAddr() { return addr; }
