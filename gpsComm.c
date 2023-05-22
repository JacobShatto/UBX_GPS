#include "gpsComm.h"

#include <rc/uart.h>

int GPS_init()
{
        gpsHeader.buffer = malloc(GPS_BUFFER_SIZE);
        gpsHeader.messageID = 0;

        return rc_uart_init(GPS_BUS, GPS_BAUDRATE, GPS_TIMEOUT, 0, 1, 0);
}

int GPS_readData()
{
        static bool validPacket[2] = { false, false };
        if (rc_uart_bytes_available(GPS_BUS))
        {
                int bytes = rc_uart_bytes_available(GPS_BUS);
                static uint8_t structBuffer[PACKAGE_LENGTH];
                static int bytesFilled = 0;

                bool packetValid = validPacket[0] && validPacket[1];

                memset(buffer, 0, sizeof(buffer));
                rc_uart_read_bytes(GPS_BUS, buffer, bytes);

                for (int i = 0; i < bytes; i++)
                {
                        if (validPacket[0] && buffer[i] == MESSAGE_CLASS)
                        {
                                validPacket[0] = true;
                        }
                        if (validPacket[1] && buffer[i] == MESSAGE_ID)
                        {
                                validPacket[1] = true;
                        }

                        if (packetValid && !structBufferFilled)
                        {
                                structBuffer[i] = buffer[i];
                                bytesFilled++;
                                if (bytesFilled == PACKAGE_LENGTH)
                                {
                                        validPacket[0] = false;
                                        validPacket[1] = false;
                                }
                        }
                }
                rc_uart_flush(GPS_BUS);
        }
}

void GPS_allocatePayloadMemory()
{
        gpsData.data = malloc(gpsPacket.header.length);
}
