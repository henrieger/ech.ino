# ifndef __TEMPERATURE_H__
# define __TEMPERATURE_H__

# include <OneWire.h>
# include <DallasTemperature.h>
# include "sensor.h"

class TemperatureSensor: public Sensor
{
    public:

        TemperatureSensor(int inputPin);

        void begin();

        long readInput();
        float readFloatInput();

    private:

        OneWire oneWire;
        DallasTemperature sensors;
};

# endif
