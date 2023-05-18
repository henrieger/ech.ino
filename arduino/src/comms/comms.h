# ifndef __COMMS_H__
# define __COMMS_H__

# include <Arduino.h>

// Markers are reversed - Arduino is little endian
const uint32_t INIT_MARKER = 0xff00ff00;
const uint32_t END_MARKER = 0x00ff00ff;
const uint16_t DATA_REQUEST = 0x5244; // little endian 'DR'
const uint16_t ACK = 0x4b41; // little endian 'AK'
# define TRIGGER 'T'

class Comms
{
    public:
        Comms();
        Comms(int _tank_id);

        void begin();

        byte checkForTrigger();
        byte checkForDataRequest();

        void sendData(uint8_t *buffer, int size);

        byte acknowledged();
        byte acknowledged(int timeout);

        int getTankID();
        int *getTankIDAddr();
        void setTankID(int tank_id);

    private:
        int tank_id;
};

uint8_t *reverse(uint8_t *buffer, int len);

# endif
