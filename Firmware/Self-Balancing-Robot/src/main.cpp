  // libraries
  #include <MPU6050_light.h>
  #include <Wire.h>

  // global variables
  // declaring pins
  const int pwm1 = 18, int1 = 19, int2 = 21;
  const int pwm2 = 22, int3 = 23, int4 = 25; 
  // MPU I2c pinss
  const int SDA_PIN = 21;
  const int SCL_PIN = 22;

  const float desiredOutput = -1.9; // desired angle (r)
  const float Kp = 80; 
  const float Ki = 120;
  const float Kd = 0.4; 
  const int minSpeed = 0; 
  



  // declare mpu object
  MPU6050 mpu(Wire);


  void setup() {
    // declaring pin modes
    pinMode(pwm1, OUTPUT);
    pinMode(int1, OUTPUT);
    pinMode(int2, OUTPUT);
    pinMode(pwm2, OUTPUT);
    pinMode(int3, OUTPUT);
    pinMode(int4, OUTPUT);

    Serial.begin(115200);             // begin Serial communication
    Wire.begin(SDA_PIN, SCL_PIN);     // explicit I2C pins for ESP32
    Wire.setWireTimeout(3000, true);  // 3ms timeout, reset on timeout
    byte mpuSucess = mpu.begin();     // confused about parameters, return byte
    if (mpuSucess == 0) {
      Serial.println("MPU connected successfully!");
    } else {
      Serial.println("MPU connecton failed.");
      while (1) {  // while true, so delay indefinitly
        delay(10);
      }
    }
    // set mpu offsets
    mpu.setAccOffsets(-0.0743398427, 0.0285234403, -0.0075678706);
    mpu.setGyroOffsets(0.7554199695, 0.7554199695, 0.7554199695);

    // configure PWM channels for ESP32
    ledcSetup(pwmChannel1, pwmFreq, pwmResolution);
    ledcAttachPin(pwm1, pwmChannel1);
    ledcSetup(pwmChannel2, pwmFreq, pwmResolution);
    ledcAttachPin(pwm2, pwmChannel2);
  }

  void setMotors(float u) {
    u = constrain(u, -255, 255);
    if (u < minSpeed && u > 0){
      u = minSpeed; 
    }
    else if (u > -minSpeed && u < 0)
    {
      u = -minSpeed;
    }
    if (u > 0) {
      digitalWrite(int1, HIGH);  
      digitalWrite(int2, LOW);
      digitalWrite(int3, LOW);
      digitalWrite(int4, HIGH);
      ledcWrite(pwmChannel1, (int)constrain(u, 0, 255));
      ledcWrite(pwmChannel2, (int)constrain(u, 0, 255));
    } else {
      digitalWrite(int1, LOW);
      digitalWrite(int2, HIGH);
      digitalWrite(int3, HIGH);
      digitalWrite(int4, LOW);
      ledcWrite(pwmChannel1, (int)constrain(-u, 0, 255));
      ledcWrite(pwmChannel2, (int)constrain(-u, 0, 255));
    }

  }
  void loop() {
    static unsigned long lastTime = 0;
    static float integral = 0;
    static float lastError = 0;
    static int printCounter = 0;

    unsigned long now = micros();
    float dt = (now - lastTime) / 1000000.0;  // seconds
    // enforce ~5ms loop period (200Hz) for consistent timing
    if (dt < 0.005) return;

    lastTime = now;
    mpu.update();                    // update data, returns void
    float angleY = mpu.getAngleY();  // declaring here to minimize scope
    
    if (abs(angleY)>60){
      digitalWrite(int1, LOW);
      digitalWrite(int2, LOW);
      digitalWrite(int3, LOW);
      digitalWrite(int4, LOW);
      while (1) { // while true, so delay indefinitly 
        delay(10); 
      }
      Serial.println("It fell..");
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

    setMotors(u);
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
      Serial.println(constrain(u, -255, 255));
      printCounter = 0;
    }
    delay(1);
  }
