#include "gpsComm.h"

GPS_Data gpsData;

int GPS_readData(uint8_t* buffer, int bufferSize)
{
        for(int i = 0; i < bufferSize; i++)
        {
                // This state machine sets gpsData.stage to the return of GPS_stageShouldChange
                switch(gpsData.stage)
                {
                case PREAMBLE_1:
                        if(buffer[i] == PREAMBLE_SYNC_CHAR_1)
                                GPS_stageShouldChange();
                        break;
                case PREAMBLE_2:
                        if(buffer[i] == PREAMBLE_SYNC_CHAR_1)
                                GPS_stageShouldChange();
                        break;
                case MESSAGE_ID:
                        break;
                case LENGTH:
                        break;
                case PAYLOAD:
                        break;
                }
        }
}

void GPS_allocatePayloadMemory()
{
        gpsData.payload = malloc(gpsData.length);
}

void GPS_stageShouldChange()
{
        // This state machine does not directly affect gpsData.stage
        switch(gpsData.stage)
        {
                case PREAMBLE_1:
                        break;
                case PREAMBLE_2:
                        break;
                case MESSAGE_ID:
                        break;
                case LENGTH:
                        break;
                case PAYLOAD:
                        break;
        }
}
