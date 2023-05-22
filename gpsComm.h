#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/**
 * UBX messages
 * 
 */

    typedef struct frame_header
    {
        uint8_t sync1, sync2, class, id;
        uint16_t length;
    } HEADER;

    struct CLASS_ID
    {
        uint8_t class, id;
        int length;
        uint8_t* payload;
    };

    typedef struct CLASS_ID UBX_ACK_ACK;
    typedef struct CLASS_ID UBX_ACK_NAK;

    typedef struct CLASS_ID UBX_CFG_ANT;
    typedef struct CLASS_ID UBX_CFG_BATCH;
    typedef struct CLASS_ID UBX_CFG_CFG;
    typedef struct CLASS_ID UBX_CFG_DAT;
    typedef struct CLASS_ID UBX_CFG_GNSS;
    typedef struct CLASS_ID UBX_CFG_INF;
    typedef struct CLASS_ID UBX_CFG_ITFM;
    typedef struct CLASS_ID UBX_CFG_MSG;
    typedef struct CLASS_ID UBX_CFG_NMEA;
    typedef struct CLASS_ID UBX_CFG_ODO;
    typedef struct CLASS_ID UBX_CFG_PRT;
    typedef struct CLASS_ID UBX_CFG_RATE;
    typedef struct CLASS_ID UBX_CFG_RST;
    typedef struct CLASS_ID UBX_CFG_VALDEL;
    typedef struct CLASS_ID UBX_CFG_VALGET;
    typedef struct CLASS_ID UBX_CFG_VALSET;



    

    uint8_t UBX_ACK_ACK[2] = {0x05, 0x01};
    uint8_t UBX_ACK_NAK[2] = {0x05, 0x00};

    uint8_t UBX_CFG_ANT[2] = {0x06, 0x13};
    uint8_t UBX_CFG_BATCH[2] = {0x06, 0x93};
    uint8_t UBX_CFG_CFG[2] = {0x06, 0x09};
    uint8_t UBX_CFG_DAT[2] = {0x06, 0x06};
    uint8_t UBX_CFG_GNSS[2] = {0x06, 0x3e};
    uint8_t UBX_CFG_INF[2] = {0x06, 0x02};
    uint8_t UBX_CFG_ITFM[2] = {0x06, 0x39};
    uint8_t UBX_CFG_MSG[2] = {0x06, 0x01};
    uint8_t UBX_CFG_NMEA[2] = {0x06, 0x17};
    uint8_t UBX_CFG_ODO[2] = {0x06, 0x1e};
    uint8_t UBX_CFG_PRT[2] = {0x06, 0x00};
    uint8_t UBX_CFG_RATE[2] = {0x06, 0x08};
    uint8_t UBX_CFG_RST[2] = {0x06, 0x04};
    uint8_t UBX_CFG_VALDEL[2] = {0x06, 0x8c};
    uint8_t UBX_CFG_VALGET[2] = {0x06, 0x8b};
    uint8_t UBX_CFG_VALSET[2] = {0x06, 0x8a};

    uint8_t UBX_MGA_ACK[2] = {0x13, 0x60};
    uint8_t UBX_MGA_ANO[2] = {0x13, 0x20};
    uint8_t UBX_MGA_BDS[2] = {0x13, 0x03};
    uint8_t UBX_MGA_DBD[2] = {0x13, 0x80};
    uint8_t UBX_MGA_GAL[2] = {0x13, 0x02};
    uint8_t UBX_MGA_GLO[2] = {0x13, 0x06};
    uint8_t UBX_MGA_GPS[2] = {0x13, 0x00};
    uint8_t UBX_MGA_INI[2] = {0x13, 0x40};
    uint8_t UBX_MGA_QZSS[2] = {0x13, 0x05};








#define GPS_BUS 2

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


