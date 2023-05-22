#include "gpsComm.h"

GPS_Data gpsData;

int GPS_init(int baud, double timeout_s)
{
        if(rc_uart_init(GPS_BUS, baud, timeout_s, 0, 1, 0))
                printf("Failed to initialize GPS uart");

        return 0;
}

int GPS_readData(uint8_t* buffer, int bufferSize)
{
        if(rc_uart_bytes_available(GPS_BUS))
        {
                bufferSize = rc_uart_bytes_available(GPS_BUS);
                memset(buffer, 0, sizeof(buffer));

                rc_uart_read_bytes(GPS_BUS, buffer, bufferSize);
                rc_uart_flush(GPS_BUS);

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
