/*
 * Semtech SX1278 LoRA radio driver library
 */
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/spi/spi.h>
#include <linux/spi/spidev.h>
#include <errno.h>

#include "sx1278.h"

int SX1278_Spi_Open(const char *path)
{
    const unsigned long spi_mode = SPI_MODE_3;
    const unsigned long spi_bits_per_word = 8;
    const unsigned long spi_speed = 100000; // 100kHz
    int ret = 0;

    if (path == NULL)
    {
        return SX_NULL;
    }

    int spi_fd = open(path, O_RDWR);
    if (spi_fd < 0)
    {
        perror("can't open device");
        return SX_ERROR_OPEN;
    }

    ret = ioctl(spi_fd, SPI_IOC_WR_MODE, &spi_mode);
    if (ret < 0)
    {
        perror("can't set spi mode");
        return SX_ERROR_OPEN;
    }

    ret = ioctl(spi_fd, SPI_IOC_RD_MODE, &spi_mode);
    if (ret < 0)
    {
        perror("can't get spi mode");
        return SX_ERROR_OPEN;
    }

    ret = ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits_per_word);
    if (ret < 0)
    {
        perror("can't set bits per word");
        return SX_ERROR_OPEN;
    }

    ret = ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bits_per_word);
    if (ret < 0)
    {
        perror("can't get bits per word");
        return SX_ERROR_OPEN;
    }

    ret = ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
    if (ret < 0)
    {
        perror("can't set max speed hz");
        return SX_ERROR_OPEN;
    }

    ret = ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
    if (ret < 0)
    {
        perror("can't get max speed hz");
        return SX_ERROR_OPEN;
    }

    return spi_fd;
}

ssize_t SX1278_Spi_Read(int fd, uint8_t *data, size_t len)
{
    return read(fd, data, len);
}

ssize_t SX1278_Spi_Write(int fd, const uint8_t *data, size_t len)
{
    return write(fd, data, len);
}

/**
 * SX1278 driver for SPI transactions
 */
static SX1278_Ops_t SX1278_Spi_Ops =
{
    .open  = SX1278_Spi_Open,
    .reset = NULL,
    .read  = SX1278_Spi_Read,
    .write = SX1278_Spi_Write,
};

/**
 * Initialize the library
 */
SX1278_Status SX1278_Init(void)
{
    return SX_SUCCESS;
}

/**
 * Close the library
 */
SX1278_Status SX1278_Finalize(void)
{
    return SX_SUCCESS;
}

/**
 * Open a device path handle to a chip
 */
SX1278_Status SX1278_Open(const char *path, SX1278_t *sx)
{
    if (sx == NULL)
    {
        return SX_NULL;
    }

    memset(sx, 0, sizeof(*sx));

    // since we only support spi operations right now, we just default the drvier to SPI operations.
    // The whole point of this driver layer is kinda obviated by the fact that this is basically a SPI
    // only chip. Still, this is useful practice and good foundations for potential future chips.
    sx->ops = &SX1278_Spi_Ops;
    if (sx->ops->open == NULL)
    {
        return SX_ERROR;
    }

    /* Open the handle */
    sx->fd = sx->ops->open(path);
    if (sx->fd < 0)
    {
        return SX_ERROR;
    }

    /* Continue with the setup */
    sx->outputpwr = SX_OP20;
    sx->bandwith = SX_BW62_5;
    sx->coderate = SX_CR8;
    sx->frequency = 433.92e6;
    sx->do_crc = true;
    sx->use_agc = true;
    sx->implicitheader = true;
    sx->syncword = 0xAA;

    return SX_SUCCESS;
}

/**
 * Reset a SX1278 chip
 */
SX1278_Status SX1278_Reset(SX1278_t *sx)
{
    // check if the struct, ops, or driver function to call are null
    if (sx == NULL || sx->ops == NULL || sx->ops->reset == NULL)
    {
        return SX_NULL;
    }

    if (sx->ops->reset(sx->fd))
    {
        return SX_SUCCESS;
    }

    return SX_ERROR;
}

/**
 * Read from a chip
 * returns: a negative number which is a library error code, or a positive number which is the bytes read
 */
ssize_t SX1278_Read(SX1278_t *sx, uint8_t *data, size_t len)
{
    if (sx == NULL || sx->ops == NULL || sx->ops->read == NULL)
    {
        return (ssize_t) SX_NULL;
    }

    return sx->ops->read(sx->fd, data, len);
}

/**
 * Write to a chip
 * returns: a negative number which is a library error code, or a positive number which is the bytes written
 */
ssize_t SX1278_Write(SX1278_t *sx, const uint8_t *data, size_t len)
{
    if (sx == NULL || sx->ops == NULL || sx->ops->write == NULL)
    {
        return (ssize_t) SX_NULL;
    }

    return sx->ops->write(sx->fd, data, len);
}

SX1278_Status SX1278_Reg_Write_Byte(SX1278_t *sx, uint8_t reg, uint8_t byte)
{
    if (sx == NULL || sx->ops == NULL || sx->ops->write == NULL)
    {
        return SX_NULL;
    }

    uint8_t data[] = {reg, byte};
    ssize_t nbytes = sx->ops->write(sx->fd, data, sizeof(data));

    if (nbytes < 0)
    {
        return SX_ERROR;
    }

    return SX_SUCCESS;
}

static uint8_t lora_reg_read_byte(SX1278_t *sx, uint8_t reg)
{
    if (sx == NULL || sx->ops == NULL || sx->ops->read == NULL)
    {
        return SX_NULL;
    }

    if (sx->fd < 0)
    {
        return SX_ERROR_OPEN;
    }

    const uint8_t tx[] = {reg, 0};
    uint8_t rx[2] = {};

    ssize_t read_result = sx->ops->read(sx->fd, rx, sizeof(rx));
    if (read_result < 0)
    {
        return SX_ERROR;
    }

    return rx[1];
}

static uint8_t lora_reg_write_byte(SX1278_t *sx, uint8_t reg)
{
    if (sx == NULL || sx->ops == NULL || sx->ops->write == NULL)
    {
        return SX_NULL;
    }

    if (sx->fd < 0)
    {
        return SX_ERROR_OPEN;
    }

    const uint8_t tx[] = {reg, 0};
    uint8_t rx[2] = {};

    ssize_t write_result = sx->ops->write(sx->fd, tx, sizeof(tx));
    if (write_result < 0)
    {
        return SX_ERROR;
    }

    return rx[1];
}

SX1278_Status SX1278_set_sleep_mode(SX1278_t *sx){
	lora_reg_write_byte(sx, REG_OP_MODE, (lora_reg_read_byte(sx, REG_OP_MODE) & 0xf8) | SLEEP_MODE );
    return SX1278_Reg_Write_Byte(sx, REG_OP_MODE, uint8_t byte);
}


// SX1278_Status SX1278_Set_LoRa_Mode(SX1278_t *sx)
// {
//     if (sx == NULL || sx->ops == NULL || sx->ops->write == NULL)
//     {
//         return SX_NULL;
//     }
// 
// 	lora_set_sleep_mode(spid);
// 	lora_reg_write_byte(spid, REG_OP_MODE, (lora_reg_read_byte(spid, REG_OP_MODE) & 0x7f) | LORA_MODE );
// }
// 
