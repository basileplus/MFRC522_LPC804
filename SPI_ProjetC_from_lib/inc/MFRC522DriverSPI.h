/* SPDX-License-Identifier: LGPL-2.1 */
#pragma once

#include "spi.h"
#include "MFRC522Constants.h"

extern Uid uid;


  //using PCD_Register = MFRC522Constants::PCD_Register;
  /////////////////////////////////////////////////////////////////////////////////////
  // Functions for setting up the Arduino.
  /////////////////////////////////////////////////////////////////////////////////////
  

/////////////////////////////////////////////////////////////////////////////////////
// Basic interface functions for communicating with the MFRC522.
/////////////////////////////////////////////////////////////////////////////////////
void PCD_WriteRegister(const unsigned char reg, const uint8_t value);
void PCD_WriteRegisterBytes(const unsigned char reg, const uint8_t count, uint8_t *const values) ;
uint8_t PCD_ReadRegister(const unsigned char reg) ;
void PCD_ReadRegisterBytes(const unsigned char reg, const uint8_t count, uint8_t *const values, const uint8_t rxAlign) ;

