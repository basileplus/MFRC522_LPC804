/* SPDX-License-Identifier: LGPL-2.1 */
#pragma once

#include <MFRC522Constants.h>
#include <MFRC522v2.h>

extern Uid uid;



  // Get human readable code and type
  const char *PICC_GetTypeName(unsigned char type);
  const char *GetStatusCodeName(unsigned char code);
  
  // Support functions for debugging
  // Injected Arduino API with Print* could be replaced by void* if required.
  void PrintUID(const Uid *uid);
  void PrintSelectedUID();
  void PCD_DumpVersionToSerial();
  
  void PICC_DumpToSerial(Uid *uid);
  void PICC_DumpDetailsToSerial(Uid *uid);
  void PICC_DumpMifareClassicToSerial(Uid *uid, unsigned char piccType, MIFARE_Key *key);
  void PICC_DumpMifareClassicSectorToSerial(Uid *uid, MIFARE_Key *key, uint8_t sector);
  void PICC_DumpMifareUltralightToSerial();

