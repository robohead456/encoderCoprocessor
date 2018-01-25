/* SPI_Encoder.h
 *  
 * SPI_Encoder library for communicating with a slave arduino attached
 *  to 5 rotary encoders.
 *  
 * Written by Michael Sidler
 * 
 */

#ifndef SPI_Encoder_h
#define SPI_Encoder_h

#include "Arduino.h"

class SPI_Encoder {
  public:
    SPI_Encoder();
    void setup();
    uint16_t getEncoderPosition(uint8_t);
  private:
    uint8_t transferDelay(uint8_t);
};

#endif

