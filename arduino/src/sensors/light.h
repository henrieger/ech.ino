# ifndef __LIGHT_H__
# define __LIGHT_H__

# include "sensor.h"
# include <BH1750.h>

class LightSensor: public Sensor
{
    public:
        LightSensor();
        LightSensor(int addr);

        void begin();

        long readInput();
        float readFloatInput();

        void setAddr(int _addr);
        int getAddr();

    private:
        int addr;
        BH1750 sensor;
};

# endif
