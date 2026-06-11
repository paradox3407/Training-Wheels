// include libraries
#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  byte mpuSucess = mpu.begin();
  if (mpuSucess == 0){
    Serial.println("MPU connected successfully!");
  }
  else {
    Serial.println("MPU connecton failed.");
    while (1) { // while true, so delay indefinitly 
      delay(10); 
    }
  }
  mpu.calcOffsets(true, true);
  float accXoffset = mpu.getAccXoffset(); 
  float accYoffset = mpu.getAccYoffset(); 
  float accZoffset = mpu.getAccZoffset(); 
  float gyroXoffset = mpu.getGyroXoffset();
  float gyroYoffset = mpu.getGyroYoffset();
  float gyroZoffset = mpu.getGyroZoffset();
  Serial.print("accXoffset: ");
  Serial.println(accXoffset, 10);
  Serial.print("accYoffset: ");
  Serial.println(accYoffset, 10);
  Serial.print("accZoffset: ");
  Serial.println(accZoffset, 10);
  Serial.print("gyroXoffset: ");
  Serial.println(gyroXoffset, 10);
  Serial.print("gyroYoffset: ");
  Serial.println(gyroYoffset, 10);
  Serial.print("gyroZoffset: ");
  Serial.println(gyroZoffset, 10);
}
void loop() {
  
}
