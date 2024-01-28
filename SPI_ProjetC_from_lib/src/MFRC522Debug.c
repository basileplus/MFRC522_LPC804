/* SPDX-License-Identifier: LGPL-2.1 */
#include "MFRC522Debug.h"
#include "MFRC522Constants.h"
#include <stdio.h>
#include "MFRC522v2.h"

extern Uid uid;
extern int version;

/**
 * Returns a char pointer to the PICC type name.
 * 
 * @return const char *
 */
const char *PICC_GetTypeName(unsigned char piccType  ///< One of the unsigned charenums.
                                                         ) {
  switch(piccType) {
    case PICC_TYPE_ISO_14443_4:
      return ("PICC compliant with ISO/IEC 14443-4");
    case PICC_TYPE_ISO_18092:
      return ("PICC compliant with ISO/IEC 18092 (NFC)");
    case PICC_TYPE_MIFARE_MINI:
      return ("MIFARE Mini, 320 bytes");
    case PICC_TYPE_MIFARE_1K:
      return ("MIFARE 1KB");
    case PICC_TYPE_MIFARE_4K:
      return ("MIFARE 4KB");
    case PICC_TYPE_MIFARE_UL:
      return ("MIFARE Ultralight or Ultralight C");
    case PICC_TYPE_MIFARE_PLUS:
      return ("MIFARE Plus");
    case PICC_TYPE_MIFARE_DESFIRE:
      return ("MIFARE DESFire");
    case PICC_TYPE_TNP3XXX:
      return ("MIFARE TNP3XXX");
    case PICC_TYPE_NOT_COMPLETE:
      return ("SAK indicates UID is not complete.");
    case PICC_TYPE_UNKNOWN:
    default:
      return ("Unknown type");
  }
} // End PICC_GetTypeName()

/**
 * Returns a char pointer to a status code name.
 * 
 * @return const char *
 */
const char *GetStatusCodeName(unsigned char code  ///< One of the unsigned char enums.
                                                          ) {
  switch(code) {
    case STATUS_OK:
      return ("Success.");
    case STATUS_ERROR:
      return ("Error in communication.");
    case STATUS_COLLISION:
      return ("collision detected.");
    case STATUS_TIMEOUT:
      return ("Timeout in communication.");
    case STATUS_NO_ROOM:
      return ("A buffer is not big enough.");
    case STATUS_INTERNAL_ERROR:
      return ("Internal error in the code. Should not happen.");
    case STATUS_INVALID:
      return ("Invalid argument.");
    case STATUS_CRC_WRONG:
      return ("The CRC_A does not match.");
    case STATUS_MIFARE_NACK:
      return ("A MIFARE PICC responded with NAK.");
    default:
      return ("Unknown error");
  }
} // End GetStatusCodeName()

//void PrintUID(, const Uid &uid) {
//  for(uint8_t i = 0; i < uid.size; i++) {
//    printf(uid.uidByte[i] < 0x10 ? " 0" : " ");
//    printf(uid.uidByte[i], HEX);
//  }
//}

#include <stdio.h>



void PrintUID(const Uid *uid) {
    for(unsigned char i = 0; i < uid->size; i++) {
        if (uid->uidByte[i] < 0x10) {
            printf(" 0");
        } else {
            printf(" ");
        }
        printf("%02X", uid->uidByte[i]);  // %02X formats the uint8_t in hexadecimal, with leading zero if necessary
    }
}


void PrintSelectedUID(const Uid *uid) {
  PrintUID(uid);
}

/**
 * Dumps debug info about the connected PCD to Serial.
 * Shows all known firmware versions.
 */
void PCD_DumpVersionToSerial() {
  // Get the MFRC522 firmware version.
  unsigned char version = PCD_GetVersion();
  
  if (version != Version_Unknown) {
      printf("Firmware Version: 0x%X", version);
  }

  // Human readable version.
  switch(version) {
    case 0xb2:
      printf((" = FM17522_1  \n"));
      break;
    case 0x88:
      printf((" = FM17522 \n"));
      break;
    case 0x89:
      printf((" = FM17522E\n"));
      break;
    case 0x90:
      printf((" = v0.0\n"));
      break;
    case 0x91:
      printf((" = v1.0\n"));
      break;
    case 0x92:
      printf((" = v2.0\n"));
      break;
    case 0x12:
      printf((" = counterfeit chip\n"));
      break;
    default:
      printf((" = (unknown)\n"));
  }
  // When 0x00 or 0xFF is returned, communication probably failed
  if(version == Version_Unknown) {
    printf(("WARNING: Communication failure, is the MFRC522 properly connected?\n"));
  }
} // End PCD_DumpVersionToSerial()

/**
 * Dumps debug info about the selected PICC to Serial.
 * On success the PICC is halted after dumping the data.
 * For MIFARE Classic the factory default key of 0xFFFFFFFFFFFF is tried.  
 */
void PICC_DumpToSerial(Uid *uid) {
  MIFARE_Key key;
  
  // Dump UID, SAK and Type
  PICC_DumpDetailsToSerial(uid);
  
  // Dump contents
  unsigned char piccType = PICC_GetType(uid->sak);
  switch(piccType) {
    case PICC_TYPE_MIFARE_MINI:
    case PICC_TYPE_MIFARE_1K:
    case PICC_TYPE_MIFARE_4K:
      // All keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
      for(uint8_t i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
      }
      PICC_DumpMifareClassicToSerial(uid, piccType, &key);
      break;
    
    case PICC_TYPE_MIFARE_UL:
      PICC_DumpMifareUltralightToSerial();
      break;
    
    case PICC_TYPE_ISO_14443_4:
    case PICC_TYPE_MIFARE_DESFIRE:
    case PICC_TYPE_ISO_18092:
    case PICC_TYPE_MIFARE_PLUS:
    case PICC_TYPE_TNP3XXX:
      printf(("Dumping memory contents not implemented for that PICC type.\n"));
      break;
    
    case PICC_TYPE_UNKNOWN:
    case PICC_TYPE_NOT_COMPLETE:
    default:
      break; // No memory dump here
  }
    PICC_HaltA(); // Already done if it was a MIFARE Classic PICC.
} // End PICC_DumpToSerial()

/**
 * Dumps card info (UID,SAK,Type) about the selected PICC to Serial.
 */
void PICC_DumpDetailsToSerial(Uid *uid) {
  // UID
  printf(("Card UID:"));
  for(uint8_t i = 0; i < uid->size; i++) {
    if(uid->uidByte[i] < 0x10)
      printf((" 0"));
    else
      printf((" "));
    printf("0x%X", uid->uidByte[i]);
  }
  
  // SAK
  printf(("\n \r Card SAK: "));
  if(uid->sak < 0x10)
    printf(("0"));
  printf("%X", uid->sak);
  
  // (suggested) PICC type
  unsigned char piccType = PICC_GetType(uid->sak);
  printf(("\n \r PICC type: "));
  printf(PICC_GetTypeName(piccType));
} // End PICC_DumpDetailsToSerial()

/**
 * Dumps memory contents of a MIFARE Classic PICC.
 * On success the PICC is halted after dumping the data.
 */
void PICC_DumpMifareClassicToSerial(
                                                  Uid *uid,      ///< Pointer to Uid struct returned from a successful PICC_Select().
                                                  unsigned char piccType,  ///< One of the unsigned charenums.
                                                  MIFARE_Key *key    ///< Key A used for all sectors.
                                                 ) {
  uint8_t no_of_sectors = 0;
  switch(piccType) {
    case PICC_TYPE_MIFARE_MINI:
      // Has 5 sectors * 4 blocks/sector * 16 bytes/block = 320 bytes.
      no_of_sectors = 5;
      break;
    
    case PICC_TYPE_MIFARE_1K:
      // Has 16 sectors * 4 blocks/sector * 16 bytes/block = 1024 bytes.
      no_of_sectors = 16;
      break;
    
    case PICC_TYPE_MIFARE_4K:
      // Has (32 sectors * 4 blocks/sector + 8 sectors * 16 blocks/sector) * 16 bytes/block = 4096 bytes.
      no_of_sectors = 40;
      break;
    
    default: // Should not happen. Ignore.
      break;
  }
  
  // Dump sectors, highest address first.
  if(no_of_sectors) {
    printf(("Sector Block   0  1  2  3   4  5  6  7   8  9 10 11  12 13 14 15  AccessBits\n \r"));
    for(int8_t i = no_of_sectors-1; i >= 0; i--) {
      PICC_DumpMifareClassicSectorToSerial(uid, key, i);
    }
  }
  PICC_HaltA(); // Halt the PICC before stopping the encrypted session.
  PCD_StopCrypto1();
} // End PICC_DumpMifareClassicToSerial()


/**
 * Dumps memory contents of a sector of a MIFARE Classic PICC.
 * Uses PCD_Authenticate(), MIFARE_Read() and PCD_StopCrypto1.
 * Always uses PICC_Command::PICC_CMD_MF_AUTH_KEY_A because only Key A can always read the sector trailer access bits.
 */
void PICC_DumpMifareClassicSectorToSerial(
                                                        Uid *uid,      ///< Pointer to Uid struct returned from a successful PICC_Select().
                                                        MIFARE_Key *key,  ///< Key A for the sector.
                                                        uint8_t sector      ///< The sector to dump, 0..39.
                                                       ) {
  unsigned char status;
  uint8_t                firstBlock;    // Address of lowest address to dump actually last block dumped)
  uint8_t                no_of_blocks;    // Number of blocks in sector
  int                isSectorTrailer;  // Set to 1 while handling the "last" (ie highest address) in the sector.
  
  // The access bits are stored in a peculiar fashion.
  // There are four groups:
  //		g[3]	Access bits for the sector trailer, block 3 (for sectors 0-31) or block 15 (for sectors 32-39)
  //		g[2]	Access bits for block 2 (for sectors 0-31) or blocks 10-14 (for sectors 32-39)
  //		g[1]	Access bits for block 1 (for sectors 0-31) or blocks 5-9 (for sectors 32-39)
  //		g[0]	Access bits for block 0 (for sectors 0-31) or blocks 0-4 (for sectors 32-39)
  // Each group has access bits [C1 C2 C3]. In this code C1 is MSB and C3 is LSB.
  // The four CX bits are stored together in a nible cx and an inverted nible cx_.
  uint8_t c1, c2, c3;    // Nibbles
  uint8_t c1_, c2_, c3_;    // Inverted nibbles
  int invertedError;    // True if one of the inverted nibbles did not match
  uint8_t g[4];        // Access bits for each of the four groups.
  uint8_t group;        // 0-3 - active group for access bits
  int firstInGroup;    // True for the first block dumped in the group
  
  // Determine position and size of sector.
  if(sector < 32) { // Sectors 0..31 has 4 blocks each
    no_of_blocks = 4;
    firstBlock   = sector*no_of_blocks;
  } else if(sector < 40) { // Sectors 32-39 has 16 blocks each
    no_of_blocks = 16;
    firstBlock   = 128+(sector-32)*no_of_blocks;
  } else { // Illegal input, no MIFARE Classic PICC has more than 40 sectors.
    return;
  }
  
  // Dump blocks, highest address first.
  uint8_t byteCount;
  uint8_t buffer[18];
  uint8_t blockAddr;
  isSectorTrailer = 1;
  invertedError   = 0;  // Avoid "unused variable" warning.
  for(int8_t blockOffset = no_of_blocks-1; blockOffset >= 0; blockOffset--) {
    blockAddr = firstBlock+blockOffset;
    // Sector number - only on first line
    if(isSectorTrailer) {
      if(sector < 10)
        printf(("   ")); // Pad with spaces
      else
        printf(("  ")); // Pad with spaces
      printf("%d", sector);
      printf(("   "));
    } else {
      printf(("       "));
    }
    // Block number
    if(blockAddr < 10)
      printf(("   ")); // Pad with spaces
    else {
      if(blockAddr < 100)
        printf(("  ")); // Pad with spaces
      else
        printf((" ")); // Pad with spaces
    }
    printf("%d", blockAddr);
    printf(("  "));
    // Establish encrypted communications before reading the first block
    if(isSectorTrailer) {
      status = PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, firstBlock, key, uid);
      if(status != STATUS_OK) {
        printf(("PCD_Authenticate() failed: "));
        printf(GetStatusCodeName(status));
        return;
      }
    }
    // Read block
    byteCount = sizeof(buffer);
    status    = MIFARE_Read(blockAddr, buffer, &byteCount);
    if(status != STATUS_OK) {
      printf(("MIFARE_Read() failed: "));
      printf(GetStatusCodeName(status));
      printf("\n \r");
      continue;
    }
    // Dump data
    for(uint8_t index = 0; index < 16; index++) {
      if(buffer[index] < 0x10)
        printf((" 0"));
      else
        printf((" "));
      printf("%X", buffer[index]);
      if((index%4) == 3) {
        printf((" "));
      }
    }
    // Parse sector trailer data
    if(isSectorTrailer) {
      c1            = buffer[7] >> 4;
      c2            = buffer[8] & 0xF;
      c3            = buffer[8] >> 4;
      c1_           = buffer[6] & 0xF;
      c2_           = buffer[6] >> 4;
      c3_           = buffer[7] & 0xF;
      invertedError = (c1 != (~c1_ & 0xF)) || (c2 != (~c2_ & 0xF)) || (c3 != (~c3_ & 0xF));
      g[0] = ((c1 & 1) << 2) | ((c2 & 1) << 1) | ((c3 & 1) << 0);
      g[1] = ((c1 & 2) << 1) | ((c2 & 2) << 0) | ((c3 & 2) >> 1);
      g[2] = ((c1 & 4) << 0) | ((c2 & 4) >> 1) | ((c3 & 4) >> 2);
      g[3] = ((c1 & 8) >> 1) | ((c2 & 8) >> 2) | ((c3 & 8) >> 3);
      isSectorTrailer = 0;
    }
    
    // Which access group is this block in?
    if(no_of_blocks == 4) {
      group        = blockOffset;
      firstInGroup = 1;
    } else {
      group        = blockOffset/5;
      firstInGroup = (group == 3) || (group != (blockOffset+1)/5);
    }
    
    if(firstInGroup) {
      // Print access bits
      printf((" [ "));
      printf("%d", (g[group] >> 2) & 1);
      printf((" "));
      printf("%d", (g[group] >> 1) & 1);
      printf((" "));
      printf("%d", (g[group] >> 0) & 1);
      printf((" ] "));
      if(invertedError) {
        printf((" Inverted access bits did not match! \n \r"));
      }
    }
    
    if(group != 3 && (g[group] == 1 || g[group] == 6)) { // Not a sector trailer, a value block
    	int32_t value = ((int32_t)buffer[3] << 24) |
    	                ((int32_t)buffer[2] << 16) |
    	                ((int32_t)buffer[1] << 8)  |
    	                (int32_t)buffer[0];
      printf((" Value=0x"));
      printf("%X", value);
      printf((" Adr=0x"));
      printf("%X", buffer[12]);
    }
  }
  
  return;
} // End PICC_DumpMifareClassicSectorToSerial()

/**
 * Dumps memory contents of a MIFARE Ultralight PICC.
 */
void PICC_DumpMifareUltralightToSerial() {
  unsigned char status;
  uint8_t       byteCount;
  uint8_t       buffer[18];
  uint8_t       i;
  
  printf(("\n \r Page  0  1  2  3"));
  // Try the mpages of the original Ultralight. Ultralight C has more pages.
  for(uint8_t page = 0; page < 16; page += 4) { // Read returns data for 4 pages at a time.
    // Read pages
    byteCount = sizeof(buffer);
    status    = MIFARE_Read(page, buffer, &byteCount);
    if(status != STATUS_OK) {
      printf(("MIFARE_Read() failed: "));
      printf(GetStatusCodeName(status));
      break;
    }
    // Dump data
    for(uint8_t offset = 0; offset < 4; offset++) {
      i = page+offset;
      if(i < 10)
        printf(("  ")); // Pad with spaces
      else
        printf((" ")); // Pad with spaces
      printf("%d", i);
      printf(("  "));
      for(uint8_t index = 0; index < 4; index++) {
        i = 4*offset+index;
        if(buffer[i] < 0x10)
          printf((" 0"));
        else
          printf((" "));
        printf("%X", buffer[i]);
      }
    }
  }
} // End PICC_DumpMifareUltralightToSerial()
