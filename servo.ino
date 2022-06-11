//#include <ESP8266WiFi.h>
#include <Servo.h>
#include <cstring>

char read_string[23];
Servo servo;

int pos = 0;

const char* ssid = "HackTM";
const char* password = "backspacehack";

void setup() {
    servo.attach(D8, 500, 2500);
    // D1 - the pin the servo is attached to
    // 500 µs - the servo's minimum supported pulse
    // 2500 µs - the servo's maximum supported pulse

    // these min&max values are specific for
    // each servo

    // if not specified in the attach function,
    // they will default to 544 and 2400
    Serial.begin(9600);
    Serial.println("Start");
    delay(1000);
}

void rotateServoDegrees(Servo servo, int degrees, int time){
    /**
     * @param: servo - The servo motor that you want to use.
     * @param: degrees - The number of position of [0, 180] degrees you want to adjust the servo motor.
     * @param: time - Rotation time.
     */

    // --------- making the rotation -------
//    int position = 500;
//    if(degrees != 0) {
//        position = (2500 * degrees) / 180;
//    } if(degrees == 90){
//        position = 1500;
//    }
    servo.write(degrees);

    // ------- printing the rotation values to the serial monitor ------
//    char message[64], degrees_2_char[10], position_2_char[10];
//    sprintf(degrees_2_char, "%d", degrees);
//    sprintf(position_2_char, "%d", position);
//
//    strcat(message, "Rotation of ");
//    strcat(message, degrees_2_char);
//    strcat(message, " = ");
//    strcat(message, position_2_char);
//    strcat(message, "µs \n");

//    Serial.write(message);
    delay(time);
}

void loop() {
    rotateServoDegrees(servo, 0, 1500);
    rotateServoDegrees(servo, 90, 1500);
    rotateServoDegrees(servo, 180, 1500);
    rotateServoDegrees(servo, 270, 1500);
    rotateServoDegrees(servo, 360, 1500);

}

void determine_stop_location(Servo servo, int time){
    for(int i = 0; i <= 180; i++){
        rotateServoDegrees(servo, i, time);
    }
}
