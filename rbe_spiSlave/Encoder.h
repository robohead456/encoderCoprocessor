/* Encoder.h
 *  
 * Encoder Library
 *  
 * Written by Michael Sidler
 * 
 */
 
#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder {
  public:
    Encoder(uint8_t, uint8_t);
    uint16_t getPos();
    void changeA();  //ISR would need to be static -> create ISR in main code to call the method for each instance
    void changeB();
  private:
    uint8_t pinA;
    uint8_t pinB;
    volatile uint16_t pos = 0; //variables changed during an interrupt must be volatile
};
#endif
