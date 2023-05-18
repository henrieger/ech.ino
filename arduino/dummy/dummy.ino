# include "src/comms/serial.h"
# include "src/sensors/sensor.h"

# include <string.h>

SerialComms serial = SerialComms(1);

void setup()
{
    delay(random(0, 5000));
    serial.begin();
}

void loop()
{
    if (serial.checkForTrigger())
    {
        delay(1500); // Simulate taking measurements

        if (serial.checkForDataRequest())
        {
            do {
                float measurement = (float) random(1, 65000);
                int sensor_type = TEMPERATURE | 0x8000;

                uint8_t buff[6];
                memcpy(buff, reverse((uint8_t *) &sensor_type, 2), 2);
                memcpy(buff+2, (uint8_t *) &measurement, 4);

                serial.sendData(buff, sizeof(int)+sizeof(float));
            } while (!serial.acknowledged());
        }
    }
    else delay(1000);
}
