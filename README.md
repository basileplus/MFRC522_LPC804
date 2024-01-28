# Advanced Arduino Driver Library for MFRC522 on LPCXpresso804

This library allows you to read and write different types of **Radio-Frequency Identification (RFID)** cards using an MFRC522-based reader module with your LPC804 board. It facilitates communication between your LPC804 board and RFID cards via the Serial Peripheral Interface (SPI) interface.

Originally based on the Arduino library found at [Arduino_MFRC522v2](https://github.com/OSSLibraries/Arduino_MFRC522v2), this library has been adapted for the NXP LPCXpresso804 board and translated from C++ to C.

The primary functionality allows you to dump information about an RFID card. This function has been thoroughly tested and confirmed to work correctly. Other functions from the original Arduino library are expected to be compatible with minimal modifications.

## Compatibility

This library supports:

- Communication (Crypto1) with MIFARE Classic cards (1k, 4k, Mini).
- Communication (Crypto1) with MIFARE Classic compatible Proximity Integrated Circuit Cards (PICCs).

## Hardware Components

- **Microcontroller**: LPCXpresso804 development board.
- **Proximity Coupling Device (PCD)**: An RFID **Reader** based on the [NXP MFRC522](https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf) Contactless Reader IC.
- **Proximity Integrated Circuit Card (PICC)**: RFID **Cards** or **Tags** using the [ISO/IEC 14443A](https://en.wikipedia.org/wiki/ISO/IEC_14443) interface (e.g., Mifare or NTAG203).

## Pinning Configuration

|**Signal**|_MFRC522_|_LPCXpresso804_ (default)|
|---|---|---|
|SPI SS|SDA|P0_21|
|SPI MOSI|MOSI|P0_18|
|SPI MISO|MISO|P0_20|
|SPI SCK|SCK|P0_19|

You can change the pin configuration at the beginning of the main file where SPI settings are set for the LPC board.

## Communication Protocol

- **Microcontroller to Reader**: Uses SPI for communication, as detailed in the [NXP MFRC522 datasheet](https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf). Refer to the [Pin Layout](https://github.com/OSSLibraries/Arduino_MFRC522v2#pin-layout) for connection details.
- **Reader to Tags**: Utilizes a 13.56 MHz electromagnetic field. The protocol is defined in ISO/IEC 14443-3:2011 Part 3 Type A (details in chapter 6, _"Type A – Initialization and anticollision"_). A free version of the final draft is available at [ISO/IEC 14443-3](https://wg8.de/wg8n1496_17n3613_Ballot_FCD14443-3.pdf). Note: The reader does not support ISO/IEC 14443-3 Type B.


