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

typedef struct SX1278_Register
{
    char *description;
    uint8_t addr;
    uint8_t por_default;
    uint8_t fsk_default;
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
REGISTER(0x0E, RegRssiConfig );
REGISTER(0x0E, RegFifoTxBaseAddr);
REGISTER(0x0F, RegRssiCollision);
REGISTER(0x0F, RegFifoRxBaseAddr);
REGISTER(0x10, RegRssiThreshFifoRxCurrentAddr);
REGISTER(0x10, RegFifoxRxCurrentAddr);
REGISTER(0x11, RegRssiValue); // RSSI value in dBm
REGISTER(0x11, RegIrqFlagsMask); // Optional IRQ flag mask
REGISTER(0x12, RegRxBw); // Channel Filter BW Control
REGISTER(0x12, RegIrqFlags); // IRQ flags
REGISTER(0x13, RegAfcBw); // AFC Channel Filter BW
REGISTER(0x13, RegRxNbBytes); // Number of received bytes
REGISTER(0x14, RegOokPeak); // Default: 0x28, OOK demodulator
REGISTER(0x14, RegRxHeaderCnt);
REGISTER(0x15, RegOokFix); // Fixed threshold of the OOK demod
REGISTER(0x15, RegRxHeaderCntValueLsb); // Number of valid headers received
REGISTER(0x16, RegOokAvg); // Average of the OOK demod
REGISTER(0x16, RegRxPacketCntValueMsb); // Number of valid packets received
REGISTER(0x17, RegRxPacketCntValueLsb); // Number of valid packets received
REGISTER(0x17, Reserved17);
REGISTER(0x18, Reserved18); // Reserved
REGISTER(0x18, RegModemStat); // 0x32 Live LoRaTM modem status

0x02 RSSI Start Tx data
0x0A RSSI Collision detectorStart Rx data
0xFF RSSI Threshold controlStart address of last packet received
0x0C Threshold of the OOK demod
ValueMsb 0x12
ValueLsb 0x47 -
0x19 Reserved19RegPktSnrValue 0x3E-
0x1A RegAfcFeiRegPktRssiValue 0x00 AFC and FEI control
Espimation of last packet
SNR
RSSI of last packet
#endif // SX1278_REGISTERS_H_
