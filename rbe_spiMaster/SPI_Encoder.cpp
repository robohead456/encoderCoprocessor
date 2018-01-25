/* SPI_Encoder.cpp
 *  
 * SPI_Encoder library for communicating with a slave arduino attached
 *  to 5 rotary encoders.
 *  
 * Written by Michael Sidler
 * 
 */

#include "Arduino.h"
#include "SPI_Encoder.h"
#include <SPI.h>

SPI_Encoder::SPI_Encoder() {}

void SPI_Encoder::setup() {
  
  // Write SS high
  digitalWrite(SS, HIGH);  

  SPI.begin();

  //Slow down the SPI clock
  //SPI.setClockDivider(SPI_CLOCK_DIV8);
}

uint8_t SPI_Encoder::transferDelay(uint8_t data) {
  uint8_t returnData = SPI.transfer(data);
  delayMicroseconds(20); //Allows the slave to process the information and return data.
  return returnData;
}

uint16_t SPI_Encoder::getEncoderPosition(uint8_t encoderNumber) {

  //Variables to  store upper and lower bytes
  uint8_t a, b;

  // enable Slave Select
  digitalWrite(SS, LOW);    

  //The data from the first transfer will be sent back after the second transfer
  //The data from the second transfer will be sent back after the third transfer
  //The data from the third transfer will be sent back after the first transfer of the next call of getEncoderPosition()
      transferDelay(encoderNumber);
  a = transferDelay(0);
  b = transferDelay(0);

  // disable Slave Select
  digitalWrite(SS, HIGH);

  return (a*256)+b;
}

