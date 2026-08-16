  // libraries
  #include <Arduino.h>
  #include <MPU6050_light.h>
  #include <Wire.h>
  #include <AccelStepper.h>

  // global variables

  // declaring stepper pins
  const int step1PIN = 19, dir1_PIN = 18;
  const int step2PIN = 5, dir2_PIN = 17; 

  // MPU I2c pins
  const int SDA_PIN = 21;
  const int SCL_PIN = 22;

  // PID variables/gains

  const float desiredOutput = 0; // desired angle 
  const float Kp = 1000; 
  const float Ki = 1;
  const float Kd = 1;
  
  const int minSpeed = 0;

  // declare mpu object
  MPU6050 mpu(Wire);

  // declare stepper objects 
  AccelStepper stepper1(1, step1PIN, dir1_PIN); 
  AccelStepper stepper2(1, step2PIN, dir2_PIN);

  void setup() {
    Serial.begin(115200);             // begin Serial communication
    Wire.begin(SDA_PIN, SCL_PIN);     // explicit I2C pins for ESP32
    //Wire.setWireTimeout(3000, true);  // 3ms timeout, reset on timeout
    byte mpuSuccess = mpu.begin();     
    if (mpuSuccess == 0) {
      Serial.println("MPU connected successfully!");
    } else {
      Serial.println("MPU connection failed.");
      while (1) {  // while true, so delay indefinitely
        delay(10);
      }
    }
    // set mpu offsets
    mpu.setAccOffsets(-0.0283935554, 0.0057998048,  -0.0133457035);
    mpu.setGyroOffsets(0.2869922817, 0.6501984596, -0.4168854356);

    stepper1.setMaxSpeed(100000);
    stepper2.setMaxSpeed(100000);

  }

  void setMotorSpeeds(float u) {
    u = constrain(u, -15000, 15000);
    stepper1.setSpeed(u);
    stepper2.setSpeed(u);
  }

  void loop() {
    static unsigned long lastTime = 0;
    static float integral = 0;
    static float lastError = 0;
    static int printCounter = 0;

    stepper1.runSpeed();
    stepper2.runSpeed();

    unsigned long now = micros();
    float dt = (now - lastTime) / 1000000.0;  // seconds
    // enforce ~5ms loop period (200Hz) for consistent timing
    if (dt < 0.005) return;

    lastTime = now;
    mpu.update();                    // update data, returns void
    float angleY = mpu.getAngleY();  // declaring here to minimize scope
    
    if (abs(angleY)>60){
      stepper1.setSpeed(0);
      stepper2.setSpeed(0);
      Serial.println("It fell..");
      while (1) { // while true, so delay indefinitely 
        delay(10); 
      }
    }
    
    float error = desiredOutput - angleY;

    // P term 
    float P = Kp * error; 

    // I term 
    integral += error * dt;
    integral = constrain(integral, -100, 100);
    float I = Ki * integral;

    // D term 
    float derivative = (error - lastError) / dt;
    float D = Kd * derivative;
    lastError = error;

    float u = P + I + D; 

    setMotorSpeeds(u);

    if (++printCounter >= 10) {
      Serial.print("Error:");
      Serial.print(error);
      Serial.print(",");
      Serial.print("Integral:");
      Serial.print(I);
      Serial.print(",");
      Serial.print("AngleY:");
      Serial.print(angleY);
      Serial.print(",");
      Serial.print("u:");
      Serial.println(u);
      printCounter = 0;
    }
    delay(1);
  }