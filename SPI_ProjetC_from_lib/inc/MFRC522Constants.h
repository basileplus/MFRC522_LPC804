/* SPDX-License-Identifier: LGPL-2.1 */
#pragma once

#include <stdint.h>



// MFRC522 registers. Described in chapter 9 of the datasheet.

// Page 0: Command and status
#define CommandReg          0x01    // starts and stops command execution
#define ComIEnReg           0x02    // enable and disable interrupt request control bits
#define DivIEnReg           0x03    // enable and disable interrupt request control bits
#define ComIrqReg           0x04    // interrupt request bits
#define DivIrqReg           0x05    // interrupt request bits
#define ErrorReg            0x06    // error bits showing the error status of the last command executed
#define Status1Reg          0x07    // communication status bits
#define Status2Reg          0x08    // receiver and transmitter status bits
#define FIFODataReg         0x09    // input and output of 64 byte FIFO buffer
#define FIFOLevelReg        0x0A    // number of bytes stored in the FIFO buffer
#define WaterLevelReg       0x0B    // level for FIFO underflow and overflow warning
#define ControlReg          0x0C    // miscellaneous control registers
#define BitFramingReg       0x0D    // adjustments for bit-oriented frames
#define CollReg             0x0E    // bit position of the first bit-collision detected on the RF interface

// Page 1: Command
#define ModeReg             0x11    // defines general modes for transmitting and receiving
#define TxModeReg           0x12    // defines transmission data rate and framing
#define RxModeReg           0x13    // defines reception data rate and framing
#define TxControlReg        0x14    // controls the logical behavior of the antenna driver pins TX1 and TX2
#define TxASKReg            0x15    // controls the setting of the transmission modulation
#define TxSelReg            0x16    // selects the internal sources for the antenna driver
#define RxSelReg            0x17    // selects internal receiver settings
#define RxThresholdReg      0x18    // selects thresholds for the bit decoder
#define DemodReg            0x19    // defines demodulator settings
#define MfTxReg             0x1C    // controls some MIFARE communication transmit parameters
#define MfRxReg             0x1D    // controls some MIFARE communication receive parameters
#define SerialSpeedReg      0x1F    // selects the speed of the serial UART interface

// Page 2: Configuration
#define CRCResultRegH       0x21    // shows the MSB and LSB values of the CRC calculation
#define CRCResultRegL       0x22
#define ModWidthReg         0x24    // controls the ModWidth setting?
#define RFCfgReg            0x26    // configures the receiver gain
#define GsNReg              0x27    // selects the conductance of the antenna driver pins TX1 and TX2 for modulation
#define CWGsPReg            0x28    // defines the conductance of the p-driver output during periods of no modulation
#define ModGsPReg           0x29    // defines the conductance of the p-driver output during periods of modulation
#define TModeReg            0x2A    // defines settings for the internal timer
#define TPrescalerReg       0x2B    // the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg.
#define TReloadRegH         0x2C    // defines the 16-bit timer reload value
#define TReloadRegL         0x2D
#define TCounterValueRegH   0x2E    // shows the 16-bit timer value
#define TCounterValueRegL   0x2F

// Page 3: Test Registers
#define TestSel1Reg         0x31    // general test signal configuration
#define TestSel2Reg         0x32    // general test signal configuration
#define TestPinEnReg        0x33    // enables pin output driver on pins D1 to D7
#define TestPinValueReg     0x34    // defines the values for D1 to D7 when it is used as an I/O bus
#define TestBusReg          0x35    // shows the status of the internal test bus
#define AutoTestReg         0x36    // controls the digital self-test
#define VersionReg          0x37    // shows the software version
#define AnalogTestReg       0x38    // controls the pins AUX1 and AUX2
#define TestDAC1Reg         0x39    // defines the test value for TestDAC1
#define TestDAC2Reg         0x3A    // defines the test value for TestDAC2
#define TestADCReg          0x3B    // shows the value of ADC I and Q channels

// MFRC522 commands. Described in chapter 10 of the datasheet.
#define PCD_Idle             0x00    // no action, cancels current command execution
#define PCD_Mem              0x01    // stores 25 bytes into the internal buffer
#define PCD_GenerateRandomID 0x02    // generates a 10-byte random ID number
#define PCD_CalcCRC          0x03    // activates the CRC coprocessor or performs a self-test
#define PCD_Transmit         0x04    // transmits data from the FIFO buffer
#define PCD_NoCmdChange      0x07    // no command change, modify CommandReg register bits without affecting the command
#define PCD_Receive          0x08    // activates the receiver circuits
#define PCD_Transceive       0x0C    // transmits data from FIFO buffer to antenna and activates the receiver after transmission
#define PCD_MFAuthent        0x0E    // performs the MIFARE standard authentication as a reader
#define PCD_SoftReset        0x0F    // resets the MFRC522

// MFRC522 RxGain[2:0] masks, receiver's signal voltage gain factor
#define RxGain_18dB          0x00 << 4    // 18 dB, minimum
#define RxGain_23dB          0x01 << 4    // 23 dB
#define RxGain_18dB_2        0x02 << 4    // 18 dB, duplicate for 000b
#define RxGain_23dB_2        0x03 << 4    // 23 dB, duplicate for 001b
#define RxGain_33dB          0x04 << 4    // 33 dB, average, typical default
#define RxGain_38dB          0x05 << 4    // 38 dB
#define RxGain_43dB          0x06 << 4    // 43 dB
#define RxGain_48dB          0x07 << 4    // 48 dB, maximum
#define RxGain_min           0x00 << 4    // 18 dB, minimum, convenience for RxGain_18dB
#define RxGain_avg           0x04 << 4    // 33 dB, average, convenience for RxGain_33dB
#define RxGain_max           0x07 << 4    // 48 dB, maximum, convenience for RxGain_48dB

// Version of chip / firmware
#define Version_Counterfeit  0x12
#define Version_FM17522      0x88
#define Version_FM17522_1    0xb2
#define Version_FM17522E     0x89
#define Version_0_0          0x90
#define Version_1_0          0x91
#define Version_2_0          0x92
#define Version_Unknown      0xff

// Commands sent to the PICC
#define PICC_CMD_REQA        0x26    // REQuest command, Type A
#define PICC_CMD_WUPA        0x52    // Wake-UP command, Type A
#define PICC_CMD_CT          0x88    // Cascade Tag, used during anti collision
#define PICC_CMD_SEL_CL1     0x93    // Anti collision/Select, Cascade Level 1
#define PICC_CMD_SEL_CL2     0x95    // Anti collision/Select, Cascade Level 2
#define PICC_CMD_SEL_CL3     0x97    // Anti collision/Select, Cascade Level 3
#define PICC_CMD_HLTA        0x50    // HaLT command, Type A
#define PICC_CMD_RATS        0xE0    // Request for Answer To Reset
#define PICC_CMD_MF_AUTH_KEY_A 0x60  // Perform authentication with Key A
#define PICC_CMD_MF_AUTH_KEY_B 0x61  // Perform authentication with Key B
#define PICC_CMD_MF_READ     0x30    // Reads one 16 byte block from the PICC
#define PICC_CMD_MF_WRITE    0xA0    // Writes one 16 byte block to the PICC
#define PICC_CMD_MF_DECREMENT 0xC0   // Decrements the contents of a block
#define PICC_CMD_MF_INCREMENT 0xC1   // Increments the contents of a block
#define PICC_CMD_MF_RESTORE  0xC2    // Reads the contents of a block into the internal data register
#define PICC_CMD_MF_TRANSFER 0xB0    // Writes the contents of the internal data register to a block
#define PICC_CMD_UL_WRITE    0xA2    // Writes one 4 byte page to the PICC

// MIFARE constants
#define MF_ACK              0xA     // MIFARE Classic 4 bit ACK/NAK
#define MF_KEY_SIZE         6       // Mifare Crypto1 key is 6 bytes

// PICC types
#define PICC_TYPE_UNKNOWN           0
#define PICC_TYPE_ISO_14443_4       1 // PICC compliant with ISO/IEC 14443-4
#define PICC_TYPE_ISO_18092         2 // PICC compliant with ISO/IEC 18092 (NFC)
#define PICC_TYPE_MIFARE_MINI       3 // MIFARE Classic protocol, 320 bytes
#define PICC_TYPE_MIFARE_1K         4 // MIFARE Classic protocol, 1KB
#define PICC_TYPE_MIFARE_4K         5 // MIFARE Classic protocol, 4KB
#define PICC_TYPE_MIFARE_UL         6 // MIFARE Ultralight or Ultralight C
#define PICC_TYPE_MIFARE_PLUS       7 // MIFARE Plus
#define PICC_TYPE_MIFARE_DESFIRE    8 // MIFARE DESFire
#define PICC_TYPE_TNP3XXX           9 // Only in NXP AN 10833 MIFARE Type Identification Procedure
#define PICC_TYPE_NOT_COMPLETE      0xff // SAK indicates UID is not complete

// Return codes
#define STATUS_OK                   0 // Success
#define STATUS_ERROR                1 // Error in communication
#define STATUS_COLLISION            2 // Collision detected
#define STATUS_TIMEOUT              3 // Timeout in communication
#define STATUS_NO_ROOM              4 // A buffer is not big enough
#define STATUS_INTERNAL_ERROR       5 // Internal error in the code
#define STATUS_INVALID              6 // Invalid argument
#define STATUS_CRC_WRONG            7 // The CRC_A does not match
#define STATUS_UNKNOWN              8
#define STATUS_MIFARE_NACK          0xff // A MIFARE PICC responded with NAK

// A struct used for passing the UID of a PICC.
typedef struct {
  uint8_t size;      // Number of bytes in the UID. 4, 7 or 10.
  uint8_t uidByte[10];
  uint8_t sak;      // The SAK (Select acknowledge) byte returned from the PICC after successful selection.
} Uid;

// A struct used for passing a MIFARE Crypto1 key.
typedef struct {
  uint8_t keyByte[6];
} MIFARE_Key;
