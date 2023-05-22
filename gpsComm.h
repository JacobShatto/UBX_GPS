#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/**
 * gpsComm.h
 */

#define PREAMBLE_SYNC_CHAR_1 0xb5
#define PREAMBLE_SYNC_CHAR_2 0x62


 /**
  * Represents which part of the gpsData is currently being recieved.
  */
enum _GPSStage {
    PREAMBLE_1,
    PREAMBLE_2,
    MESSAGE_ID,
    LENGTH,
    PAYLOAD,
    CHECKSUM_A,
    CHECKSUM_B,
    PACKET_COMPLETE
};
typedef enum _GPSStage GPS_Stage;

/*
 * Each part of the gps data used in the UBX protocol
 */
typedef struct gps_Data {
    uint16_t messageID;
    uint16_t length;
    uint8_t* payload;
    GPS_Stage stage;
    uint32_t checkSum_A;
    uint32_t checkSum_B;

} GPS_Data;

extern GPS_Data gpsData;

/**
 * Function to get the size of the payload in bytes
 *
 * @return gpsData.length (bytes)
 */
inline uint16_t GPS_getPayloadSize() { return gpsData.length; }

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
