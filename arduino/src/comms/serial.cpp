# include "serial.h"

SerialComms::SerialComms(int tank_id)
{
    setTankID(tank_id);
}

void SerialComms::begin()
{
    Serial.begin(9600);
    Serial.setTimeout(0);
    reverse((uint8_t *) getTankIDAddr(), sizeof(int));

    Serial.write((uint8_t *) &INIT_MARKER, sizeof(uint32_t));
    Serial.write((uint8_t *) getTankIDAddr(), sizeof(int));
    Serial.write((uint8_t *) &END_MARKER, sizeof(uint32_t));
    Serial.flush();
}

byte SerialComms::checkForTrigger()
{
    if (Serial.available() <= 0) return 0;

    uint32_t buffer;

    Serial.readBytes((uint8_t *) &buffer, sizeof(uint32_t));
    if (buffer != INIT_MARKER) return 0;

    byte result = (Serial.read() == TRIGGER);

    Serial.readBytes((uint8_t *) &buffer, sizeof(uint32_t));
    if (buffer != END_MARKER) return 0;

    Serial.flush();
    return result;
}

byte SerialComms::checkForDataRequest()
{
    if (Serial.available() <= 0) return 0;

    uint32_t buffer32;
    uint16_t buffer16;

    Serial.readBytes((uint8_t *) &buffer32, sizeof(uint32_t));
    if (buffer32 != INIT_MARKER) return 0;

    Serial.readBytes((uint8_t *) &buffer16, sizeof(uint16_t));
    byte result = (buffer16 == DATA_REQUEST);

    Serial.readBytes((uint8_t *) &buffer16, sizeof(uint16_t));
    if (buffer16 != getTankID()) return 0;

    Serial.readBytes((uint8_t *) &buffer32, sizeof(uint32_t));
    if (buffer32 != END_MARKER) return 0;

    Serial.flush();
    return result;
}

void SerialComms::sendData(uint8_t *buffer, int size)
{
    Serial.write((uint8_t *) &INIT_MARKER, sizeof(uint32_t));
    Serial.write((uint8_t *) (uint8_t *) getTankIDAddr(), sizeof(int));
    Serial.write(buffer, size);
    Serial.write((uint8_t *) &END_MARKER, sizeof(uint32_t));
    Serial.flush();
}

byte SerialComms::acknowledged()
{
    return acknowledged(5);
}

// TODO: Disable timeout in edge cases
byte SerialComms::acknowledged(int timeout)
{
    Serial.setTimeout(timeout * 1000);

    // Delay for checking availability of serial bus
    delay(50);

    if (Serial.available() <= 0) return 0;

    uint32_t buffer32;
    uint16_t buffer16;

    Serial.readBytes((uint8_t *) &buffer32, sizeof(uint32_t));
    if (buffer32 != INIT_MARKER) return 0;

    Serial.readBytes((uint8_t *) &buffer16, sizeof(uint16_t));
    byte result = (buffer16 == ACK);

    Serial.readBytes((uint8_t *) &buffer16, sizeof(uint16_t));
    if (buffer16 != getTankID()) return 0;

    Serial.readBytes((uint8_t *) &buffer32, sizeof(uint32_t));
    if (buffer32 != END_MARKER) return 0;

    Serial.setTimeout(0);
    Serial.flush();
    return result;
}
