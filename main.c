#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rc/uart.h>

#include "gpsComm.h"

#define BUFFER_SIZE 200
#define TIMEOUT_S 0.5
#define BAUDRATE 115200

int main()
{

        uint8_t buffer[BUFFER_SIZE];
        int ret;
        int bus = 2;

        if(rc_uart_init(bus, BAUDRATE, TIMEOUT_S, 0, 1, 0))
                printf("Failed to load rc_uart_init");
        printf("Uart initialized on port: %d\n", bus);

        int bytes;
        while(1)
        {
                if(rc_uart_bytes_available(bus))
                {
                        bytes = rc_uart_bytes_available(bus);
                        printf("Bytes available: %d\n", bytes);

                        memset(buf, 0, sizeof(buffer));

                        ret = rc_uart_read_bytes(bus, buffer, bytes);

                        printf("%s\n", buffer);

                        GPS_readData(buffer);

                        rc_uart_flush(bus);
                }
        }
        rc_uart_close(bus);
        return 0;
}
