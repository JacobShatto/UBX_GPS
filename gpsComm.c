#include "gpsComm.h"

#include <rc/uart.h>

GPS_Packet gpsPacket;

int GPS_init()
{
        gpsHeader.buffer = malloc(GPS_BUFFER_SIZE);
        gpsHeader.messageID = 0;

        return rc_uart_init(GPS_BUS, GPS_BAUDRATE, GPS_TIMEOUT, 0, 1, 0);
}

int GPS_readData()
{
        if (rc_uart_bytes_available(GPS_BUS) == 6 && gpsPacket.state = WAITING_HEADER)
        {
                gpsPacket.bufferSize = rc_uart_bytes_available(GPS_BUS);
                memset();
                gpsPacket.header = *(GPS_Header*)gpsPacket.buffer;
                GPS_alocatePayloadMemory();
                gpsPacket.state = WAITING_PAYLOAD;
        }
        else if (rc_uart_bytes_available(GPS_BUS) == gpsPacket.header.length)
        {
                
        }
}

void GPS_allocatePayloadMemory()
{
        gpsData.data = malloc(gpsPacket.header.length);
}
