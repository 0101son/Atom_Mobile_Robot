#include "ibus.h"

bool IBus::init()
{
    serialRef->begin(115200);
    return true;
}

int IBus::readChannel(uint8_t channelNr)
{
    if (channelNr < IBUS_MAXCHANNELS)
    {
        return channelWidths[channelNr];
    }
    else
    {
        return -1; // 채널 범위를 벗어남
    }
}

void IBus::readRx()
{
    rxFrameDone = false;

    if (serialRef->available())
    {
        uint8_t val = serialRef->read();

        // Look for 0x2040 as start of packet
        if (ibusIndex == 0 && val != 0x20)
        {
            ibusIndex = 0;
            return;
        }
        if (ibusIndex == 1 && val != 0x40)
        {
            ibusIndex = 0;
            return;
        }

        if (ibusIndex == IBUS_BUFFSIZE)
        {
            ibusIndex = 0;
            int high = 3;
            int low = 2;

            for (int i = 0; i < IBUS_MAXCHANNELS; i++)
            {
                rcValue[i] = (ibus[high] << 8) + ibus[low];
                high += 2;
                low += 2;
            }

            for (int i = 0; i < IBUS_MAXCHANNELS; i++)
            {
                channelWidths[i] = map(rcValue[i], 1000, 2000, 1000, 2000);
            }

            rxFrameDone = true;
            return;
        }
        else
        {
            ibus[ibusIndex] = val;
            ibusIndex++;
        }
    }
}