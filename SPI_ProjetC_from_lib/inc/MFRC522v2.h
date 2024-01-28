/* SPDX-License-Identifier: LGPL-2.1 */
/**
 * Library to use Arduino MFRC522 module.
 * 
 * @authors Dr.Leong, Miguel Balboa, Søren Thing Andersen, Tom Clement, many more! See GitLog.
 * 
 * Please read this file for an overview and then MFRC522v2.cpp for comments on the specific functions.
 */
#ifndef MFRC522_h
#define MFRC522_h

//#include <require_cpp11.h>
//#include <deprecated.h>
// Enable integer limits
#define __STDC_LIMIT_MACROS

#include <stdint.h>
#include <MFRC522Constants.h>

extern Uid uid;


// Firmware data for self-test
// Reference values based on firmware version
// Hint: if needed, you can remove unused self-test data to save flash memory
//
// Version 0.0 (0x90)
// Philips Semiconductors; Preliminary Specification Revision 2.0 - 01 August 2005; 16.1 self-test
extern const uint8_t MFRC522_firmware_referenceV0_0[];
// Version 1.0 (0x91)
// NXP Semiconductors; Rev. 3.8 - 17 September 2014; 16.1.1 self-test
extern const uint8_t MFRC522_firmware_referenceV1_0[];
// Version 2.0 (0x92)
// NXP Semiconductors; Rev. 3.8 - 17 September 2014; 16.1.1 self-test
extern const uint8_t MFRC522_firmware_referenceV2_0[];
// Clone
// Fudan Semiconductor FM17522 (0x88)
extern const uint8_t FM17522_firmware_reference88[];
// Another "FM17522" ic form Aliexpress
extern const uint8_t FM17522_firmware_referenceB2[];
// Fudan Semiconductor FM17522E (0x89)
extern const uint8_t FM17522E_firmware_reference[];


  
// Size of the MFRC522 FIFO
static const uint8_t FIFO_SIZE = 64;    // The FIFO is 64 uint8_ts.

// Member variables
extern Uid uid;                // Used by PICC_ReadCardSerial().


/////////////////////////////////////////////////////////////////////////////////////
// Basic interface functions for communicating with the MFRC522
/////////////////////////////////////////////////////////////////////////////////////
void PCD_SetRegisterBitMask(unsigned char reg, uint8_t mask);
void PCD_ClearRegisterBitMask(unsigned char reg, uint8_t mask);
unsigned char PCD_CalculateCRC(uint8_t *data, uint8_t length, uint8_t *result);

/////////////////////////////////////////////////////////////////////////////////////
// Functions for manipulating the MFRC522
/////////////////////////////////////////////////////////////////////////////////////
int PCD_Init();
void PCD_Reset();
void PCD_AntennaOn();
void PCD_AntennaOff();
uint8_t PCD_GetAntennaGain();
void PCD_SetAntennaGain(uint8_t mask);

unsigned char PCD_GetVersion();
int PCD_PerformSelfTest();

/////////////////////////////////////////////////////////////////////////////////////
// Power control functions
/////////////////////////////////////////////////////////////////////////////////////
void PCD_SoftPowerDown();
void PCD_SoftPowerUp();

/////////////////////////////////////////////////////////////////////////////////////
// Functions for communicating with PICCs
/////////////////////////////////////////////////////////////////////////////////////
unsigned char PCD_TransceiveData(uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint8_t *backLen, uint8_t *validBits, uint8_t rxAlign, int checkCRC);
unsigned char PCD_CommunicateWithPICC(uint8_t command, uint8_t waitIRq, uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint8_t *backLen , uint8_t *validBits, uint8_t rxAlign, int checkCRC);
unsigned char PICC_RequestA(uint8_t *bufferATQA, uint8_t *bufferSize);
unsigned char PICC_WakeupA(uint8_t *bufferATQA, uint8_t *bufferSize);
unsigned char PICC_REQA_or_WUPA(uint8_t command, uint8_t *bufferATQA, uint8_t *bufferSize);
unsigned char PICC_Select(Uid *uid, uint8_t validBits);
unsigned char PICC_HaltA();

/////////////////////////////////////////////////////////////////////////////////////
// Functions for communicating with MIFARE PICCs
/////////////////////////////////////////////////////////////////////////////////////
unsigned char PCD_Authenticate(uint8_t command, uint8_t blockAddr, MIFARE_Key *key, Uid *uid);
void PCD_StopCrypto1();
unsigned char MIFARE_Read(uint8_t blockAddr, uint8_t *buffer, uint8_t *bufferSize);
unsigned char MIFARE_Write(uint8_t blockAddr, uint8_t *buffer, uint8_t bufferSize);
unsigned char MIFARE_Ultralight_Write(uint8_t page, uint8_t *buffer, uint8_t bufferSize);
unsigned char MIFARE_Decrement(uint8_t blockAddr, int32_t delta);
unsigned char MIFARE_Increment(uint8_t blockAddr, int32_t delta);
unsigned char MIFARE_Restore(uint8_t blockAddr);
unsigned char MIFARE_Transfer(uint8_t blockAddr);
unsigned char MIFARE_GetValue(uint8_t blockAddr, int32_t *value);
unsigned char MIFARE_SetValue(uint8_t blockAddr, int32_t value);
unsigned char PCD_NTAG216_AUTH(const uint8_t password[4], uint8_t pACK[]);

/////////////////////////////////////////////////////////////////////////////////////
// Support functions
/////////////////////////////////////////////////////////////////////////////////////
unsigned char PCD_MIFARE_Transceive(uint8_t *sendData, uint8_t sendLen, int acceptTimeout);
unsigned char PICC_GetType(uint8_t sak);

// Advanced functions for MIFARE
void MIFARE_CalculateAccessBits(uint8_t accessBitBuffer[3], const uint8_t g0, const uint8_t g1, const uint8_t g2, const uint8_t g3);

  /////////////////////////////////////////////////////////////////////////////////////
  // Convenience functions - does not add extra functionality
  /////////////////////////////////////////////////////////////////////////////////////
int PICC_IsNewCardPresent();
int PICC_ReadCardSerial();


unsigned char MIFARE_TwoStepHelper(uint8_t command, uint8_t blockAddr, int32_t data);


#endif
