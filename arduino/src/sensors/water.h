# ifndef __WATER_H__
# define __WATER_H__

# include "sensor.h"

class WaterSensor: public Sensor
{
    public:

        WaterSensor(int inputPin);

        void begin(int buttonPin, int potentiometerPin, int buzzerPin);

        void warnOfWaterLevel();
        int getThreshold();
        long readInput();

        int getButtonPin();
        void setButtonPin(int _buttonPin);
        int getButtonInput();

        int getPotentiometerPin();
        void setPotentiometerPin(int _potentiometerPin);

        int getBuzzerPin();
        void setBuzzerPin(int _buzzerPin);

        int getWaterBaseInput();
        void setWaterBaseInput(int _waterBaseInput);
        void resetWaterBaseInput();

    private:

        int buttonPin, potentiometerPin, buzzerPin;
        long waterBaseInput;
};

# endif
