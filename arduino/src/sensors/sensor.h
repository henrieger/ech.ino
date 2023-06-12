# ifndef __SENSOR_H__
# define __SENSOR_H__

typedef enum
{
    WATER,
    TEMPERATURE,
    LIGHT,
    PH,
    OXYGEN 
} sensor_type;

class Sensor {
    public:
        Sensor();
        Sensor(sensor_type, int _inputPin);

        long readInput();

        sensor_type getSensorType();
        void setSensorType(sensor_type _type);

        int getInputPin();
        void setInputPin(int _inputPin);

    private:
        sensor_type type;
        int inputPin;
};

# endif
