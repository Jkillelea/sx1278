#ifndef SX1278_REGISTERS_H_
#define SX1278_REGISTERS_H_

#include <stdint.h>

/**
 * Register definitions for the SX1278 LoRa module
 */
#define SX_REG_FIFO 0x00
#define SX_REG_OP_MODE 0x01
#define SX_REG_FR_MSB 0x06
#define SX_REG_FR_DIM 0x07
#define SX_REG_FR_LSB 0x08
#define SX_REG_PA_CONFIG 0x09
#define SX_REG_OCP 0x0B

typedef struct SX1278_Register {
    char *description;
    uint8_t addr;
    uint8_t por_default;
    uint8_t fsk_default;
    uint8_t _padding;
} SX1278_Register;

#define REGISTER(address, name) const SX1278_Register (name) = {.addr = (address), .description = "", .por_default = 0, .fsk_default = 0}

// Address Register Name            Reset Default Description
//         FSK/OOK Mode LoRaTM Mode (POR) (FSK)   FSK Mode LoRaTM Mode
REGISTER(0x00, RegFifo       ); // FIFO read/write access. Default: 0x00
REGISTER(0x01, RegOpMode     ); // Operating mode & LoRaTM / FSK selection. Default: 0x01
REGISTER(0x02, RegBitrateMsb ); // Bit Rate setting, Most Significant Bits. Not used for LoRa. Default: 0x1A
REGISTER(0x03, RegBitrateLsb ); // Bit Rate setting, Least Significant Bits. Not used for LoRa. Default: 0x0B
REGISTER(0x04, RegFdevMsb    ); // Frequency Deviation setting, Most Significant Bits. Not used for LoRa. Default: 0x00
REGISTER(0x05, RegFdevLsb    ); // Frequency Deviation setting, Least Significant Bits. Not used for LoRa. Default: 0x52
REGISTER(0x06, RegFrfMsb     ); // RF Carrier Frequency, Most Significant Bits. Default: 0x6C
REGISTER(0x07, RegFrfMid     ); // RF Carrier Frequency, Intermediate Bits. Default: 0x80
REGISTER(0x08, RegFrfLsb     ); // RF Carrier Frequency, Least Significant Bits. Default: 0x00
REGISTER(0x09, RegPaConfig   ); // PA selection and Output Power control. Default: 0x4F
REGISTER(0x0A, RegPaRamp     ); // Control of PA ramp time, low phase noise PLL. Default: 0x09
REGISTER(0x0B, RegOcp        ); // Over Current Protection control. Default: 0x2B
REGISTER(0x0C, RegLna        ); // LNA settings. Default: 0x20
REGISTER(0x0D, RegRxConfig   ); // AFC, AGC, ctrl. Not used for LoRa. Default: 0x08
REGISTER(0x0D, RegFifoAddrPtr); // FIFO SPI pointer. LoRa only. Default: 0x0E

0x0E RegRssiConfig
0x0E RegFifoTxBaseAddr
0x0F RegRssiCollision
0x10 RegRssiThreshFifoRxCurrentAddr
0x11 RegRssiValue RegAfcBwRegIrqFlagsMask
RegFifoRxBa-
seAddr
0x02 RSSI Start Tx data
0x0A RSSI Collision detectorStart Rx data
0xFF RSSI Threshold controlStart address of last
packet received
0x15
0x0B RSSI value in dBm
Channel Filter BW Control
AFC Channel Filter BWOptional IRQ flag mask
IRQ flags
Number of received bytes
0x12
0x13
RegRxBw
RegIrqFlags
RegRxNbBytes 0x14 RegOokPeakRegRxHeaderCnt
ValueMsb 0x28 OOK demodulator
0x15 RegOokFixRegRxHeaderCnt
ValueLsb 0x0C Threshold of the OOK demod
0x16 RegOokAvgRegRxPacketCnt
ValueMsb 0x12 Average of the OOK demod
0x17 Reserved17RegRxPacketCnt
ValueLsb 0x47 -
0x18 Reserved18RegModemStat 0x32-
0x19 Reserved19RegPktSnrValue 0x3E-
0x1A RegAfcFeiRegPktRssiValue 0x00 AFC and FEI control
Number of valid headers
received
Number of valid packets
received
Live LoRaTM modem
status
Espimation of last packet
SNR
RSSI of last packet
#endif // SX1278_REGISTERS_H_
