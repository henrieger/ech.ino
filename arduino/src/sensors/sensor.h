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
        Sensor(sensor_type, int);
        Sensor(sensor_type, int, int *);

        int readInput();

        sensor_type getSensorType();
        void setSensorType(sensor_type);

        int getInputPin();
        void setInputPin(int);

    private:
        sensor_type type;
        int inputPin;
};

# endif
