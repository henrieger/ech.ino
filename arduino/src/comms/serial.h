# ifndef __COMMS_SERIAL_H__
# define __COMMS_SERIAL_H__

# include "comms.h"

class SerialComms: public Comms
{
    public:
        
        SerialComms(int tank_id);

        void begin();

        byte checkForTrigger();

        void sendData(uint8_t *measurement);
};

# endif
