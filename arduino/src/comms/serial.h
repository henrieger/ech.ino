# ifndef __COMMS_SERIAL_H__
# define __COMMS_SERIAL_H__

# include "comms.h"

class SerialComms: public Comms
{
    public:
        
        SerialComms(int tank_id);

        void begin();

        byte checkForTrigger();
        byte checkForDataRequest();

        void sendData(uint8_t *buffer, int size);

        byte acknowledged();
        byte acknowledged(int timeout);
};

# endif
