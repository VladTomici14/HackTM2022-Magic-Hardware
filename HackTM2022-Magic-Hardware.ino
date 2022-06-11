#include <Servo.h>

Servo servo;
int servoPower = D3;
int servoSignal = D8;

void startServo() {
    digitalWrite(servoPower, HIGH);
    digitalWrite(D4, HIGH);
    Serial.println("Start servo");
}

void stopServo() {
    digitalWrite(servoPower, LOW);
    digitalWrite(D4, LOW);
    Serial.println("Stop servo");
}

void setDirection(int dir) {
    if (dir == 1) {
        servo.write(0);
        return;
    }
    if (dir == -1) {
        servo.write(180);
        return;
    }
    stopServo();
}

void setup() {
    servo.attach(servoSignal, 500, 2500);
    Serial.begin(9600);
    Serial.println("Start");
    delay(1000);
}

void loop() {
    startServo();
    setDirection(1);
    delay(1000);
    setDirection(-1);
    delay(1000);
    setDirection(0);
    delay(1000);
    Serial.println("Loop");
}

