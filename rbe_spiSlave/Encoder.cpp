/* Encoder.h
 *  
 * Encoder Library
 *  
 * Written by Michael Sidler
 * 
 */

#include "Arduino.h"
#include "Encoder.h"

uint8_t pinA, pinB;
volatile uint16_t pos = 0;

Encoder::Encoder(uint8_t A, uint8_t B) {
  pinA = A;
  pinB = B;
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
}

uint16_t Encoder::getPos(){
  return pos;
}

void Encoder::changeA() {
  if (digitalRead(pinA)) { 
    if (digitalRead(pinB)) pos++; // A==HIGH && B==HIGH : CW 
    else pos--; // A==HIGH && B==LOW : CCW
  }
  else { 
    if (digitalRead(pinB)) pos--; // A==LOW && B==HIGH : CCW
    else pos++; // A==LOW && B==LOW : CW
  }
}

void Encoder::changeB() {
  if (digitalRead(pinB)) {   
    if (digitalRead(pinA)) pos--; // B==HIGH && A==HIGH : CCW
    else pos++; // B==HIGH && A==LOW : CW
  }
  else { 
    if (digitalRead(pinA)) pos++; // B==LOW && A==HIGH : CW
    else pos--; // B==LOW && A==LOW : CCW
  }
}

/* Quadrature Encoder Waveforms
     _____       _____
A   |     |     |     |
____|     |_____|     |_
        _____       _____
B      |     |     |     |
   ____|     |_____|     |_
--> CW
<-- CCW
*/
