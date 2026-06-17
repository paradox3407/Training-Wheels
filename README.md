<img width="949" height="933" alt="Screenshot 2026-06-16 010036" src="https://github.com/user-attachments/assets/33ced204-fea6-49c0-b08b-195e1566d54b" />

# Training Wheels

ESP32 based two wheeled self balancing robot with a custom PCB, chassis, firmware! Want to learn how to implement a control loop or just want to build a cool robot? Training Wheels is for you! 

## Features

- PID Control Algorithm 
- IMU Calibration Program
- Convenient Troubleshooting:
  - Headers for swapping ICs: ESP32, MPU6050, A4988 Stepper Motor Driver Breakout
  - LED indicators for VDD and GPIO 
- Nema 17 Stepper Motors
- Power Switch


## Overview

This project was made for [Hackclub's](https://hackclub.com/programs) Fallout Program. I built this because I wanted to make a project that encompasses mechanical, electrical, and software engineering, all while exploring PID control through implementing the prototyping process and good design practices. Through the ~70 hours spent on this project I learned the value of documentation, time management, how to select components, read datasheets, how to CAD using assemblies and designing in context, schematic, part layout and wiring good practices, version control, PID control theory and tuning, and so much more! (Might have gotten a caffeine addiction too...)


## Gallery 

<details>
  <summary> Click to expand </summary>
  <br>

  ### Chassis / Assembly
  *Designed in Onshape* 
  
  Source Files found [here](https://cad.onshape.com/documents/563a6cb8d162cb6cd823a1f9/w/2660c435afac39828b2200f7/e/e81ee193bff4145dfd9a22a6)

  <p align="center">
    <img width="607" height="933" alt="Screenshot 2026-06-16 010238" src="https://github.com/user-attachments/assets/20d90fa9-5498-4d31-8a8c-7351772157d1" />
    <img width="703" height="966" alt="Screenshot 2026-06-16 010210" src="https://github.com/user-attachments/assets/a0d517b1-b1d8-4ae3-bec7-32470eecb58b" />
  </p>

  ### PCB 
  *Designed in KiCad*

  <p align="center">
    <img width="1077" height="920" alt="Screenshot 2026-06-16 174314" src="https://github.com/user-attachments/assets/1ed5fff1-4801-4fbb-b494-bb096011044b" />
  </p>

  #### Schematic
  <img width="100%" alt="Schematic" src="https://github.com/user-attachments/assets/865efe3e-3a1d-4a05-bc29-a6e57ddf9ef7" />

  #### Layout
  <img width="100%" alt="PCB Layout" src="https://github.com/user-attachments/assets/714766f9-14b1-4638-81a3-7358a8016356" />

</details>

## Firmware (Setup + Tuning)

*Written in C++ using VSCode + [PlatformIO](https://platformio.org/)*

### How to Build & Flash
1. Clone this repository.
2. Open the `Firmware/Self-Balancing-Robot` folder in VS Code with PlatformIO installed.
3. Connect your ESP32 via USB.
4. Click the PlatformIO **Upload** button 

The IMU must be calibrated before running the main code. Run the [calibration program](./Firmware/Self-Balancing-Robot/src/calibration/MPU_calibration.cpp) while the robot is upright and in a stable position. 

### How to Tune

Then run the [main code](./Firmware/Self-Balancing-Robot/src/robot_main/main.cpp). To get the robot to balance, modify these values:

```cpp
const float desiredOutput = 0; // desired angle 
const float Kp = 0; 
const float Ki = 0;
const float Kd = 0; 
```
Tune these values in the following order: 
`desiredOutput` is used for setting the offset for the balance point of the robot. 

`Kp` is the proportional gain, and it will be doing most of the "work": increase by powers of two until the robot oscillates, then decrease by 20%.

`Kd` is the derivative gain, and it addresses oscillations. Increase by small increments, starting roughly at 0.05, until the robot stops oscillating. 

`Ki` is the integral gain, which address drift. By this point the robot should be balancing but if it glides forward or backwards, increase this value, also starting small. Note that `Ki` might not always need to be modified. 

The key to tuning is patience! Only modify one value at a time, and increment in small values. 

## Zine

*Designed in Figma*

<img width="1500" height="2303" alt="Training Wheels Zine-Final-1" src="https://github.com/user-attachments/assets/b05d9276-83e3-4d60-8f45-cbc28fbe558c" />

## Acknowledgements

Designed by Sara C / paradox3407

**Special thanks** to my robotics mentors for reviewing my designs and giving me much needed feedback! + Jennifer for creating inspiration/reference sketches for the chassis + Ellie for teaching me the basics of calculus at flex when I was trying to learn the math behind PID + Hackclub and Fallout!
