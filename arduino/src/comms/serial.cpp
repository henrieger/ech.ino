# include "serial.h"

SerialComms::SerialComms(int tank_id)
{
    setTankID(tank_id);
}

void SerialComms::begin()
{
    Serial.begin(9600);

    Serial.write(INIT_MARKER);
    Serial.write((uint8_t *) getTankIDAddr(), sizeof(int));
    Serial.write(END_MARKER);
}

byte SerialComms::checkForTrigger()
{
    if (Serial.available() <= 0) return 0;
    return Serial.read() == TRIGGER;
}

void SerialComms::sendData(uint8_t *measurement)
{
    Serial.write(INIT_MARKER);
    Serial.write((uint8_t *) getTankIDAddr(), sizeof(int));
    Serial.write(measurement, sizeof(float));
    Serial.write(END_MARKER);
}
