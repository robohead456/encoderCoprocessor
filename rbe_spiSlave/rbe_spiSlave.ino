/* rbe_spiSlave.ino
 * 
 * Slave code to read 5 rotary encoder interrupts and respond to SPI
 *  requests for their value
 *  
 * Written by Michael Sidler
 * 
 * This code uses the EnableInterrupt Library, which can be found at:
 * https://github.com/GreyGnome/EnableInterrupt
 */

#include "Encoder.h"
#include <EnableInterrupt.h>

// to store encoder number
volatile uint8_t enc = 0;

volatile uint16_t dataToSend;

Encoder enc1(A0,A1), enc2(A2,A3), enc3(2,3), enc4(4,5), enc5(6,7), enc6(8,9);

//Encoder interrupt service routines
void ISR_enc1a(){enc1.changeA();}
void ISR_enc1b(){enc1.changeB();}
void ISR_enc2a(){enc2.changeA();}
void ISR_enc2b(){enc2.changeB();}
void ISR_enc3a(){enc3.changeA();}
void ISR_enc3b(){enc3.changeB();}
void ISR_enc4a(){enc4.changeA();}
void ISR_enc4b(){enc4.changeB();}
void ISR_enc5a(){enc5.changeA();}
void ISR_enc5b(){enc5.changeB();}
void ISR_enc6a(){enc6.changeA();}
void ISR_enc6b(){enc6.changeB();}

void setup(void) {

  enableInterrupt(A0, ISR_enc1a, CHANGE);
  enableInterrupt(A1, ISR_enc1b, CHANGE);
  enableInterrupt(A2, ISR_enc2a, CHANGE);
  enableInterrupt(A3, ISR_enc2b, CHANGE);
  enableInterrupt( 2, ISR_enc3a, CHANGE);
  enableInterrupt( 3, ISR_enc3b, CHANGE);
  enableInterrupt( 4, ISR_enc4a, CHANGE);
  enableInterrupt( 5, ISR_enc4b, CHANGE);
  enableInterrupt( 6, ISR_enc5a, CHANGE);
  enableInterrupt( 7, ISR_enc5b, CHANGE);
  enableInterrupt( 8, ISR_enc6a, CHANGE);
  enableInterrupt( 9, ISR_enc6b, CHANGE);
  
  enc = 1; //default to encoder 1

  //Set the slave output pin to an output
  pinMode(MISO, OUTPUT);

  /*  The SPCR is the SPI Control Register
   *   
   *   Bit:       7     6     5     4     3     2     1     0     
   *   Function:  SPIE  SPE   DORD  MSTR  CPOL  CPHA  SPR1  SPR0
   *   
   *   SPIE:  SPI Interrupt Enable
   *   SPE:   SPI Enable
   *   DORD:  Data Order
   *   CPOL:  Clock Polarity
   *   CPHA:  Clock Phase
   *   SPR1:  Clock Rate Select 1
   *   SPR0:  Clock Rate Select 0
   *   
   *   More information can be found at 
   *   http://avrbeginners.net/architecture/spi/spi.html
   *   http://maxembedded.com/2013/11/the-spi-of-the-avr/
   */
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  // turn on interrupts
  SPCR |= _BV(SPIE);  
}

// SPI interrupt routine
ISR (SPI_STC_vect) {
  
  /* The SPDR is the SPI Data Register
   *  
   *  It is an 8 bit register. We need to send 16 bits.
   *  These switch statements break up the 16 bits into the most and least
   *  significant 8 bits. It sends the MS bits when it recieves an encoder
   *  number and the LS bits of the last encoder number recieved when a 0
   *  is recieved. The SPI_Encoder library used by the master arduino 
   *  reconstructs the number and passes it on to the program.
   * 
   */
  uint8_t data = SPDR;

  //if recieving a 0 it means send the lower half of the last encoder number recieved
  if(data == 0) {
    //send lower half of dataToSend
    SPDR = (uint8_t)(dataToSend);
  }

  //if recieving a # it means send the upper half of that encoder number
  else {

    //set encoder number to the data recieved
    enc = data;

    //store the position of the encoder to prevent it from changing while being sent
    switch(enc) {
      case 1:
        dataToSend = enc1.getPos();
        break;
      case 2:
        dataToSend = enc2.getPos();
        break;
      case 3:
        dataToSend = enc3.getPos();
        break;
      case 4:
        dataToSend = enc4.getPos();
        break;
      case 5:
        dataToSend = enc5.getPos();
        break;
      case 6:
        dataToSend = enc6.getPos();
        break;
      default:
        dataToSend = 0xffff;
        enc = 1;
        break;
    }

    //send upper half of data
    SPDR = (uint8_t)(dataToSend >> 8);
  }
}

void loop(void) {}

