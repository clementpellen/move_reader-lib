// #include "mpu/mpu_data_save.h"
#include "mpu/acceleration_reader.h"

Acceleration_reader mpu{};


void setup() {

  Serial.begin(9600);

}

void loop() {
  
  mpu.use();

  mpu.displayPreviousAccelerationsVectorSize();

  delay(500);
}