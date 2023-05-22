#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/**
 * gpsComm.h
 */

 /**
  * GPS comm defines
 */
#define PREAMBLE_SYNC_CHAR_1 0xb5
#define PREAMBLE_SYNC_CHAR_2 0x62

 /**
  * UART defines
 */
#define GPS_BUFFER_SIZE 64
#define GPS_TIMEOUT 0.5
#define GPS_BAUDRATE 115200
#define GPS_BUS 2

 /**
  * Represents which part of the gpsData is currently being recieved.
  */
enum _GPSState
{
    WAITING_HEADER,
    WAITING_PAYLOAD,
};
typedef enum _GPSState GPS_State;

enum _PacketType {
    DEFAULT
};
typedef enum _PacketType PacketType;

/*
 * Each part of the gps data used in the UBX protocol
 */
typedef struct gps_Header
{
    uint8_t syncChar1;
    uint8_t syncChar2;
    uint8_t messageClass;
    uint8_t messageID;
    uint16_t length;

} GPS_Header;

typedef struct gps_Packet
{
    GPS_Header header;
    int bufferSize;
    uint8_t buffer[GPS_BUFFER_SIZE];
    uint8_t* data;
    uint8_t checksum[2];
}

extern GPS_Packet gpsPacket;

/**
 * Function to initialize GPS communication
 *
 * @return 0 on success -1 on failure
*/
int GPS_init();

/**
 * Function to allocate space fot eht incoming message
 */
void GPS_allocatePayloadMemory();

/**
 * Function to update the gps stage.
 *
 * Usage: Only use when
 *
 * @return Stage the gps should be at
 */
void GPS_stageShouldChange();

/**
 * Function to read and parse data
 *
 * @return 0 on success -1 on failure
 */
int GPS_readData();
