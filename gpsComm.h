/**
 * @file gpsComm.h
 * @author Jacob Shatto and Andrew McGrellis
 * 
 * @brief Implementation of u-blox M10 SPG 5.00, for M10 GPS modules 
 * Based on the following documetation: https://content.u-blox.com/sites/default/files/u-blox%20M10-SPG-5.00_InterfaceDescription_UBX-20053845.pdf
 * 
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
 * @brief GPS data frame
 * 
 */
typedef struct gps_body {

    uint8_t syncChar1; // start bits of frame
    uint8_t syncChar2; // start bits of frame

    uint8_t messageClass; // message type identifier
    uint8_t messageID; // message type identifier
    uint16_t length; // length of payload

    
    uint32_t iTOW; // GPS time of week of the navigation epoch.

    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;

    bool validDate; // 1 = valid UTC date
    bool validTime; // 1 = valid UTC time of day
    bool fullyResolved; // 1 = UTC time of day has been fully resolved (no seconds uncertainty)
    bool validMag; // 1 = valid magnetic declination

    uint32_t tAcc; // time accuracy estimate
    uint32_t nano;

    /**
     * GNSS fix type
     * 0 = no fix
     * 1 = dead reckoning only
     * 2 = 2D fix
     * 3 = 3D fix
     * 4 = GNSS + dead reckoning combined
     * 5 = time fix only
     */
    uint8_t fixtype; // fix status flags
    

    bool gnssFixOk; // 1 = valid fix within DOP and accuracy masks
    bool diffSoln; // 1 = differential corrections were applied

    /**
     * power save mode state
     * 0 = PSM is not active
     * 1 = enabled
     * 2 = acquisition
     * 3 = tracking
     * 4 = power optimized tracking
     * 5 = inactive 
     */
    bool psmState[3];


    bool headVehValid; // 1 = heading of vehicle is valid, only used in sensor fusion mode

    /**
     * carrier phase range solution status
     * 0 = no carrier phase range solution
     * 1 = carrier phase range solution with floating ambiguities
     * 2 = carrier phase range solution with fixed ambiguities
     */
    bool carrSoln[2];

    bool confirmedAvai; // 1 = information about validity comfirmation is available
    bool confirmedDate; // 1 = UTC date validity could be confirmed
    bool confirmedTime; // 1 = UTC time of day could be confirmed

    uint8_t sumSv; // number of satellites used in Nav solution
    uint32_t lon; // longitutde
    uint32_t lat; // latitude
    uint32_t height; // height above ellipsoid

    uint32_t hMSL; // height above mean sea level
    uint32_t hACC; // horizontal accuracy estimate
    uint32_t vAcc; // vertical accuracy estimate
    uint32_t velN; // NED north velocity
    uint32_t velE; // NED east velocity
    uint32_t velD; // NED down velocity
    uint32_t gSpeed; // 2D ground speed

    uint32_t headMot; // 2D heading of motion
    uint32_t sAcc; // speed accuracy estimate
    uint32_t headAcc; // heading accuracy estimate
    uint16_t pDop; // position diution of precision

    bool invalidLlh; // 1 = invalid longitude,latitude, height and hMSL

    /**
     * age of the most recently recieved differential correction
     * 0 = not available
     * 1 =  0 < age < 1
     * 2 =  1 <= age < 2
     * 3 =  2 <= age < 5
     * 4 =  5 <= age < 10
     * 5 =  10 <= age < 15
     * 6 =  15 <= age < 20
     * 7 =  20 <= age < 30
     * 8 =  30 <= age < 45
     * 9 =  45 <= age < 60
     * 10 = 60 <= age < 90
     * 11 = 90 <= age < 120
     * >=12 = age >= 120
     */
    bool lastCorrectionAge[4]; 

    bool reserved0[4]; // reserved

    uint32_t headVeh; // 2D heading of vehicle
    uint16_t magDec; // magnetice declination
    uint16_t magAcc; // magnetice declination accuracy


    uint8_t checksum[2]; // checksum of payload
} GPS_frame;


uint8_t buffer[GPS_BUFFER_SIZE];

/**
 * @brief Function to read and parse GPS data
 *
 * @return 0 on success -1 on failure
 */
int GPS_readData();

/**
 * @brief Function to initialize GPS communication
 *
 * @return 0 on success -1 on failure
*/
int GPS_init();

/**
 * @brief Function to allocate space fot the incoming message
 */
void GPS_allocatePayloadMemory();

/**
 * @brief Function to update the gps stage.
 *
 * Usage: Only use when
 *
 * @return Stage the gps should be at
 */
void GPS_stageShouldChange();


