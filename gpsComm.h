#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/**
 * UBX messages
 * 
 */

typedef struct gps_body {
    uint8_t syncChar1;
    uint8_t syncChar2;
    uint8_t messageClass;
    uint8_t messageID;
    uint16_t length;

    
    uint32_t iTOW;

    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;

    bool validDate;
    bool validTime;
    bool fullyResolved;
    bool validMag;

    uint32_t tAcc;
    uint32_t nano;

    uint8_t fixtype;
    
    bool gnssFixOk;
    bool diffSoln;
    bool psmState[3];
    bool headVehValid;
    bool carrSoln[2];

    bool confirmedAvai;
    bool confirmedDate;
    bool confirmedTime;

    uint8_t sumSv;
    uint32_t lon;
    uint32_t lat;
    uint32_t height;

    uint32_t hMSL;
    uint32_t hACC;
    uint32_t vAcc;
    uint32_t velN;
    uint32_t velE;
    uint32_t velD;
    uint32_t gSpeed;

    uint32_t headMot;
    uint32_t sAcc;
    uint32_t headAcc;
    uint16_t pDop;

    bool invalidLlh;
    bool lastCorrectionAge[4];

    bool reserved0[4];

    uint32_t headVeh;
    uint16_t magDec;
    uint16_t magAcc;


    uint8_t checksum[2];
} GPS_Body;

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

uint8_t buffer[GPS_BUFFER_SIZE];

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

struct gps_Packet
{
    GPS_Header header;
    GPS_Body body;
};

extern GPS_Packet gpsPacket;

/**
 * Function to read and parse data
 *
 * @return 0 on success -1 on failure
 */
int GPS_readData();

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


