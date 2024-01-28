/* SPDX-License-Identifier: LGPL-2.1 */
#include "MFRC522DriverSPI.h"

extern Uid uid;

/////////////////////////////////////////////////////////////////////////////////////
// Basic interface functions for communicating with the MFRC522DriverSPI
/////////////////////////////////////////////////////////////////////////////////////

void PCD_WriteRegister(const unsigned char reg, const uint8_t value){
	uint8_t data[] = {reg<<1, value};
	uint32_t dataLength = sizeof(data);
	SPImasterWriteOnly(data, dataLength);
}
  
//void PCD_WriteRegisterBytes(const unsigned char reg, const uint8_t count, uint8_t *const values) {
//	for (uint8_t i = 0; i < count; ++i) {
//		  uint8_t data[] = {(reg << 1), values[i]};
//		  uint32_t dataLength = sizeof(data);
//		  SPImasterWriteOnly(data, dataLength);
//	}
//}

void PCD_WriteRegisterBytes(const unsigned char reg, const uint8_t count, uint8_t *const values) {
	uint8_t data[count+1];
	data[0]=(reg<<1);
	for (uint8_t i = 0; i < count; ++i) {
		  data[i+1] = values[i];
	}
	uint32_t dataLength = sizeof(data);
	SPImasterWriteOnly(data, dataLength);
}

uint8_t PCD_ReadRegister(const unsigned char reg) {
  	uint8_t WrBuffer[1] = {0x80 | (reg << 1)};
  	uint8_t RdBuffer[1] = {0};  // Initialize all bytes to 0
  	int WrBufferLength = sizeof(WrBuffer);
  	SPImasterWriteRead(WrBuffer, RdBuffer, WrBufferLength);
  	return RdBuffer[0];
 } // End PCD_ReadRegister()

void PCD_ReadRegisterBytes(const unsigned char reg, const uint8_t count, uint8_t *const values, const uint8_t rxAlign) {
    if (count == 0) {
        return;
    }
    uint8_t WrBuffer[1] = {0x80 | (reg << 1)};  // Command to read from 'reg'
    uint8_t RdBuffer[1];
    SPImasterWriteRead(WrBuffer, RdBuffer, 1);  // Perform the first SPI read
    // Apply rxAlign for the first byte read.
    if (rxAlign) {
        // Create bit mask for bit positions rxAlign..7
        uint8_t mask = (0xFF << rxAlign) & 0xFF;
        // Apply mask to both current value of values[0] and the new data in RdBuffer[0].
        values[0] = (values[0] & ~mask) | (RdBuffer[0] & mask);
    } else {
        values[0] = RdBuffer[0];
    }
    // Read remaining bytes, if any
    for (uint8_t i = 1; i < count; ++i) {
        SPImasterWriteRead(WrBuffer, RdBuffer, 1);  // Read next byte
        values[i] = RdBuffer[0];
    }
}



