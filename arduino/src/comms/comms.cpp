# include "comms.h"

Comms::Comms() {}

Comms::Comms(int _tank_id)
{
    tank_id = _tank_id;
};

int Comms::getTankID() { return tank_id; }
int *Comms::getTankIDAddr() { return &tank_id; }
void Comms::setTankID(int _tank_id) { tank_id = _tank_id; }

uint8_t *reverse(uint8_t *buffer, int len)
{
    uint8_t tmp;
    for (int i = 0; i < len/2; i++)
    {
        tmp = buffer[i];
        buffer[i] = buffer[len - 1 - i];
        buffer[len - 1 -i] = tmp;
    }

    return buffer;
}
