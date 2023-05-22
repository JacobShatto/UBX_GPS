#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * gpsComm.h
 */

 /**
  * GPS comm defines
 */
#define PREAMBLE_SYNC_CHAR_1 0xb5
#define PREAMBLE_SYNC_CHAR_2 0x62

#define MESSAGE_CLASS 0x01
#define MESSAGE_ID 0x07

#define PACKAGE_LENGTH 94

 /**
  * UART defines
 */
#define GPS_BUFFER_SIZE 128
#define GPS_TIMEOUT 0.5
#define GPS_BAUDRATE 115200
#define GPS_BUS 2

uint8_t buffer[GPS_BUFFER_SIZE];

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


