// libraries
#include <MPU6050_light.h>
#include <Wire.h>

// declare mpu object
MPU6050 mpu(Wire);
int staticVariable = 0; 
float gyroX; 
float accX; 
float angleX; 

void setup(){
  Serial.begin(9600); // begin Serial communication: 9600 is standard, not too fast for chip
  Wire.begin(); // begins I2c communication, when no arguments, assumes bus to be controller
  byte mpuSucess = mpu.begin(); // confused about parameters, return byte
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
  // Serial.print("GyroX offset: ");
  // Serial.println(mpu.getGyroXoffset());
}
void loop(){
  mpu.update(); // update data, returns void
  accX = mpu.getAccX();
  gyroX = mpu.getGyroX();
  angleX = mpu.getAngleX();
  Serial.print("AccelerationX:"); // print acceleration of x axis
  Serial.print(accX);
  Serial.print(",");
  Serial.print("AngleX:");
  Serial.print(angleX);
  Serial.print(",");
  Serial.print("GyroX:"); // print angular speed around x axis
  //Serial.print(",");
  Serial.println(gyroX);
  //Serial.println(staticVariable);
  delay(1);
}