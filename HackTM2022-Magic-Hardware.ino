#include "WEMOS_Motor.h"

int pwm;

//Motor shiled I2C Address: 0x30
//PWM frequency: 1000Hz(1kHz)
Motor M1(0x30,_MOTOR_A, 1000);//Motor A
Motor M2(0x30,_MOTOR_B, 1000);//Motor B

void setup() {
    Serial.begin(9600);
}

void loop() {
    M1.setmotor(_CW, 100);
    delay(3000);
    M1.setmotor(_STOP);
    delay(1000);
    M1.setmotor(_CCW, 100);
    delay(3000);
    M1.setmotor(_STOP);
    delay(1000);
}
