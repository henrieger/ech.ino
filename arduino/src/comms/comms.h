# ifndef __COMMS_H__
# define __COMMS_H__

# include <Arduino.h>

# define INIT_MARKER '<'
# define END_MARKER '>'
# define TRIGGER 'T'

class Comms
{
    public:
        Comms();
        Comms(int _tank_id);

        void begin();

        byte checkForTrigger();

        void sendData(uint8_t *measurement);

        int getTankID();
        int *getTankIDAddr();
        void setTankID(int tank_id);

    private:
        int tank_id;
};

# endif
