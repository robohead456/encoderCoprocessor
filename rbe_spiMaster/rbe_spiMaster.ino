/* rbe_spiMaster.ino
 * 
 * Master code demo to show the features of the interrupt coprocessor.
 *  Communicates over SPI to the slave to retrieve the 5 encoder values
 *  
 * Written by Michael Sidler
 * 
 */

#include "SPI_Encoder.h"

//Create Encoder
SPI_Encoder enc;

void setup(void) {

  //Start serial for debug printing
  Serial.begin(115200);
  Serial.println("Starting Demo Sketch");

  //Setup encoder and SPI
  enc.setup();
}

uint16_t enc1, enc2, enc3, enc4, enc5, enc6;

void loop(void) {

  enc1 = enc.getEncoderPosition(1);
  enc2 = enc.getEncoderPosition(2);
  enc3 = enc.getEncoderPosition(3);
  enc4 = enc.getEncoderPosition(4);
  enc5 = enc.getEncoderPosition(5);
  enc6 = enc.getEncoderPosition(6);

  Serial.print("enc1: ");
  Serial.println(enc1);
  Serial.print("enc2: ");
  Serial.println(enc2);
  Serial.print("enc3: ");
  Serial.println(enc3);
  Serial.print("enc4: ");
  Serial.println(enc4);
  Serial.print("enc5: ");
  Serial.println(enc5);
  Serial.print("enc6: ");
  Serial.println(enc6);

  Serial.println();
  
  delay (1000);  // 1 second delay 
}

