# include "sensor.h"

# include <stdlib.h>
# include <string.h>

int getSize(int *arr)
{
    int size = 0;
    for (int i = 0; arr[i] != -1; i++)
        size++;

    return size * sizeof(int);
}

Sensor::Sensor() {
    return;
}

Sensor::Sensor(sensor_type _type, int _inputPin)
{
    type = _type;
    inputPin = _inputPin;
}

sensor_type Sensor::getSensorType() { return type; }
void Sensor::setSensorType(sensor_type _type) { type = _type; }

int Sensor::getInputPin() { return inputPin; }
void Sensor::setInputPin(int _inputPin) { inputPin = _inputPin; }

int Sensor::readInput() { return 0; }
