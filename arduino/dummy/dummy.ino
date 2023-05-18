# include "src/comms/serial.h"
# include "src/sensors/sensor.h"

# include <string.h>

SerialComms serial = SerialComms(1);
byte waiting = true;

float measurement1;
long measurement2;
int sensor_type1, sensor_type2;

void setup()
{
    randomSeed(analogRead(0));
    delay(random(0, 5000));
    serial.begin();
}

void loop()
{
    if (waiting && serial.checkForTrigger())
    {
        waiting = false;
        delay(1500); // Simulate taking measurements

        measurement1 = (float) random(1, 65000);
        sensor_type1 = TEMPERATURE | 0x8000;

        measurement2 = (long) random(-10, 10);
        sensor_type2 = WATER;
    }

    if (!waiting && serial.checkForDataRequest())
    {
        waiting = true;

        uint8_t buff[12];
        memcpy(buff,   reverse((uint8_t *) &sensor_type1, 2), 2);
        memcpy(buff+2, reverse((uint8_t *) &measurement1, 4), 4);
        memcpy(buff+6, reverse((uint8_t *) &sensor_type2, 2), 2);
        memcpy(buff+8, reverse((uint8_t *) &measurement2, 4), 4);

        do
        {
            serial.sendData(buff, (sizeof(int)+sizeof(float))*2);
        } while (!serial.acknowledged(30)); 
    }

    delay(5000);
}
