#include <stdint.h>
#include <stdio.h>
#include "sx1278.h"

int main()
{
    SX1278_Status status = SX_SUCCESS;

    status = SX1278_Init();
    if (status != SX_SUCCESS)
    {
        fprintf(stderr, "SX1278_Init failed: %d\n", status);
        return -1;
    }

    SX1278_t sx = {};
    status = SX1278_Open("/dev/spidev0.0", &sx);
    if (status != SX_SUCCESS)
    {
        fprintf(stderr, "SX1278_Open failed: %d\n", status);
        return -1;
    }


    uint8_t buffer[256] = {0};

    ssize_t read_result = SX1278_Read(&sx, buffer, sizeof(buffer));
    if (read_result < 0)
    {
        fprintf(stderr, "SX1278_Read failed: %zd\n", read_result);
        return -1;
    }
    else
    {
        fprintf(stdout, "SX1278_Read : %zd\n", read_result);
    }

    ssize_t write_result = SX1278_Write(&sx, buffer, sizeof(buffer));
    if (read_result < 0)
    {
        fprintf(stderr, "SX1278_Write failed: %zd\n", read_result);
        return -1;
    }
    else
    {
        fprintf(stdout, "SX1278_Write : %zd\n", read_result);
    }

    status = SX1278_Finalize();
    if (status != SX_SUCCESS)
    {
        fprintf(stderr, "SX1278_Finalize failed: %d\n", status);
        return -1;
    }

    return 0;
}
