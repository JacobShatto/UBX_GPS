#include "gpsComm.h"

#include <rc/uart.h>

GPS_Frame gpsFrame;

int GPS_init()
{
        gpsHeader.buffer = malloc(GPS_BUFFER_SIZE);
        gpsHeader.messageID = 0;

        return rc_uart_init(GPS_BUS, GPS_BAUDRATE, GPS_TIMEOUT, 0, 1, 0);
}

int GPS_readData()
{
        static bool validPacket[2] = { false, false };
        int bytes = rc_uart_bytes_available(GPS_BUS);
        if (bytes == PACKAGE_LENGTH)
        {
                if (buffer[2] == MESSAGE_CLASS && buffer[3] == MESSAGE_ID)
                {
                        gpsFrame = *(GPS_Frame*)buffer;
                }
                rc_uart_flush(GPS_BUS);
        }
}
