#include <stdio.h>
#include "LPC8xx.h"
#include "spi.h"
#include "syscon.h"
#include "swm.h"
#include "utilities.h"
#include "lib_ENS_II1_lcd_v2.h"
#include "MFRC522Constants.h"



/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example showing how to read data from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/OSSLibraries/Arduino_MFRC522v2
 *
 * Example sketch/program showing how to read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 *
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shift+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the ID/UID, type and any data blocks it can read. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 *
 * If your reader supports it, this sketch/program will read all the PICCs presented (that is: multiple tag reading).
 * So if you stack two or more PICCs on top of each other and present them to the reader, it will first output all
 * details of the first and then the next PICC. Note that this may take some time as all data blocks are dumped, so
 * keep the PICCs at reading distance until complete.
 *
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * Not found? For more see: https://github.com/OSSLibraries/Arduino_MFRC522v2#pin-layout
 */

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include "MFRC522Debug.h"
#include <stdlib.h>
#include <uart.h>
//#include <MFRC522DriverI2C.h>
//#include <MFRC522Debug.h>



    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4).

Uid uid;  // Definition of the global variable uid
int version ;  // Init MFRC522 board.


void printBuffer(const uint8_t *buffer, uint8_t count) {
    for (uint8_t i = 0; i < count; ++i) {
        printf("0x%02X ", buffer[i]);
    }
    printf("\n");
}

int main(void){
	// Setup LPC804
	extern void setup_debug_uart(void);

	#define SPIBAUD 115200
	#define SCK_PIN P0_19
	#define MOSI_PIN P0_18
	#define SSEL_PIN P0_21
	#define MISO_PIN P0_20


	 // Configure the debug uart (see Serial.c)
 	 setup_debug_uart();
	 // Enable clocks to relevant peripherals
	 LPC_SYSCON->SYSAHBCLKCTRL0 |= ( SWM | GPIO | SPI0 | IOCON |UART0);
	 // Provide main_clk as function clock to SPI0
	 LPC_SYSCON->SPI0CLKSEL = FCLKSEL_MAIN_CLK;
	 // Configure the SWM (see peripherals_lib and swm.h)
	 ConfigSWM(SPI0_SCK, SCK_PIN);
	 ConfigSWM(SPI0_MOSI, MOSI_PIN);
	 ConfigSWM(SPI0_SSEL0, SSEL_PIN);
	 ConfigSWM(SPI0_MISO,  MISO_PIN);
	 // Give SPI0 a reset
	 LPC_SYSCON->PRESETCTRL[0] &= (SPI0_RST_N);
	 LPC_SYSCON->PRESETCTRL[0] |= ~(SPI0_RST_N);
	 // Get main_clk frequency
	 SystemCoreClockUpdate();
	 // Configure the SPI master's clock divider (value written to DIV divides by value+1)
	 LPC_SPI0->DIV = (main_clk/SPIBAUD) - 1;
	 // Configure the CFG register:
	 // Enable=true, master, no LSB first, CPHA=0, CPOL=0, no loop-back, SSEL active low
	 LPC_SPI0->CFG = SPI_CFG_ENABLE | SPI_CFG_MASTER  ;
	 // Add delay between frames

	 // Configure the SPI delay register (DLY)
	 // Pre-delay = 0 clocks, post-delay = 0 clocks, frame-delay = 3 clocks, transfer-delay = 0 clocks
	 LPC_SPI0->DLY = SPI_DLY_FRAMEDELAY(3) | SPI_DLY_PREDELAY(3) | SPI_DLY_POSTDELAY(3) | SPI_DLY_INTERDELAY(3)  ;
	 // Configure the SPI control register
	 // Master: End-of-frame true, End-of-transfer true, RXIGNORE (SPI_CTL_RXIGNORE) true, LEN 8 bits.
	 LPC_SPI0->TXCTL = SPI_CTL_EOF | SPI_CTL_EOT  | SPI_CTL_LEN(8) ;
	 //Initialisation de l'afficheur lcd et affichage d'un texte
	 init_lcd();
	 lcd_puts("RFID Dump Info");
	 version = PCD_Init();

	 LPC_SYSCON->UART0CLKSEL = FCLKSEL_FRG0CLK;

	   // Give USART0 a reset
	   LPC_SYSCON->PRESETCTRL0 &= (UART0_RST_N);
	   LPC_SYSCON->PRESETCTRL0 |= ~(UART0_RST_N);

	   // Configure the USART0 baud rate generator
	   LPC_USART0->BRG = 97;

	   // Configure the USART0 CFG register:
	   // 8 data bits, no parity, one stop bit, no flow control, asynchronous mode
	   LPC_USART0->CFG = DATA_LENG_8|PARITY_NONE|STOP_BIT_1;

	   // Configure the USART0 CTL register (nothing to be done here)
	   // No continuous break, no address detect, no Tx disable, no CC, no CLRCC
	   LPC_USART0->CTL = 0;

	   // Clear any pending flags, just in case
	   LPC_USART0->STAT = 0xFFFF;

	   // Enable USART0
	   LPC_USART0->CFG |= UART_EN;
	   uint32_t data = 0x5555;
	   uint8_t dataBytes[2];
	   dataBytes[0] = (data >> 8) & 0xff;
	   dataBytes[1] = data & 0xff;
	while(1){
		//printf("\n \r Scan PICC to see UID, SAK, type, and data blocks...\n \r");
		// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.


		if ( PICC_IsNewCardPresent()) {
			// Select one of the cards.
			printf("New card detected \n \r");
			if ( PICC_ReadCardSerial()) {

				// Dump debug info about the card; PICC_HaltA() is automatically called.
				PICC_DumpToSerial(&uid);
			}
		}

	}
	return 0;
}



