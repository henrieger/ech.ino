# include "src/comms/serial.h"

SerialComms serial = SerialComms(1);

void setup()
{
    serial.begin();
}

void loop()
{
    if (serial.checkForTrigger())
    {
        delay(1500); // Simulate taking measurements

        float measurement = (float) random(1, 65000);
        serial.sendData((uint8_t *) &measurement);
    }
    else delay(1000);
}
