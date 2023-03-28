# include "temperature.h"

TemperatureSensor::TemperatureSensor(int inputPin)
{
    setSensorType(TEMPERATURE);
    setInputPin(inputPin);

    oneWire = OneWire(inputPin);
    sensors = DallasTemperature(&oneWire);
}

void TemperatureSensor::begin()
{
    sensors.begin();
    sensors.setResolution(12); 
}

float TemperatureSensor::readFloatInput()
{
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}

int TemperatureSensor::readInput()
{
    return (int) readFloatInput();
}
