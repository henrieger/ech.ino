# include "comms.h"

Comms::Comms() {}

Comms::Comms(int _tank_id)
{
    tank_id = _tank_id;
};

int Comms::getTankID() { return tank_id; }
int *Comms::getTankIDAddr() { return &tank_id; }
void Comms::setTankID(int _tank_id) { tank_id = _tank_id; }
