#ifndef _SX1278_H_
#define _SX1278_H_

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include "sx1278_registers.h"

/**
 * Library status return codes
 */
typedef enum
{
    SX_SUCCESS =  0, // Operation succeeded
    SX_ERROR   = -1, // Unspecified error
    SX_NULL    = -2, // Null pointer
    SX_ERROR_OPEN = -3, // Failed to open
} SX1278_Status;

// Output Power
typedef enum
{
    SX_OP0 = 0,
    SX_OP1 = 1,
    SX_OP2 = 2,
    SX_OP3 = 3,
    SX_OP4 = 4,
    SX_OP5 = 5,
    SX_OP6 = 6,
    SX_OP7 = 7,
    SX_OP8 = 8,
    SX_OP9 = 9,
    SX_OP10 = 10,
    SX_OP11 = 11,
    SX_OP12 = 12,
    SX_OP13 = 13,
    SX_OP14 = 14,
    SX_OP15 = 15,
    SX_OP16 = 16,
    SX_OP17 = 17,
    SX_OP20 = 20,
} SX1278_OutputPower;

// Bandwidth
typedef enum
{
    SX_BW7_8 = 0,
    SX_BW10_4 = 1 << 4,
    SX_BW15_6 = 2 << 4,
    SX_BW20_8 = 3 << 4,
    SX_BW31_25 = 4 << 4,
    SX_BW41_7 = 5 << 4,
    SX_BW62_5 = 6 << 4, // 62.5 kHz
    SX_BW125 = 7 << 4,
    SX_BW250 = 8 << 4,
    SX_BW500 = 9 << 4,
} SX1278_Bandwidth;

// Spreading Factor
typedef enum
{
    SX_SF7 = 7 << 4,
    SX_SF8 = 8 << 4,
    SX_SF9 = 9 << 4,
    SX_SF10 = 10 << 4,
    SX_SF11 = 11 << 4,
    SX_SF12 = 12 << 4,
} SX1278_SpreadingFactor;


// Code Rate
typedef enum
{
    SX_CR5 = 1 << 1,
    SX_CR6 = 2 << 1,
    SX_CR7 = 3 << 1,
    SX_CR8 = 4 << 1,
} SX1278_CodeRate;

/**
 * Operations outside the library, like read, write, and reset
 */
typedef struct
{
    int     (*open)(const char *path);
    bool    (*reset)(int fd);
    ssize_t (*read)(int fd, uint8_t *data, size_t len);
    ssize_t (*write)(int fd, const uint8_t *data, size_t len);
} SX1278_Ops_t;

/**
 * Basic handle type
 */
typedef struct
{
    SX1278_Ops_t *ops; // Interface operations
    SX1278_OutputPower outputpwr;
    SX1278_Bandwidth bandwith;
    SX1278_CodeRate coderate;
    double frequency;
    int fd;
    bool do_crc;
    bool use_agc;
    bool implicitheader;
    uint8_t syncword;
} SX1278_t;

/**
 * Initialize the library
 */
SX1278_Status SX1278_Init(void);

/**
 * Close the library
 */
SX1278_Status SX1278_Finalize(void);

/**
 * Open a device path handle to a chip
 */
SX1278_Status SX1278_Open(const char *path, SX1278_t *sx);

/**
 * Reset a SX1278 chip
 */
SX1278_Status SX1278_Reset(SX1278_t *sx);

/**
 * Read from a chip
 * returns: a negative number which is a library error code, or a positive number which is the bytes read
 */
ssize_t SX1278_Read(SX1278_t *sx, uint8_t *data, size_t len);

/**
 * Write to a chip
 * returns: a negative number which is a library error code, or a positive number which is the bytes written
 */
ssize_t SX1278_Write(SX1278_t *sx, const uint8_t *data, size_t len);

#endif // _SX1278_H_

