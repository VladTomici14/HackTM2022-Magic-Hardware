// This file contains some functions that may help debugging in the future.


#include <Servo.h>

char read_string[23];
Servo servo;

void setup(){
    servo.attach(D8, 500, 2500);

    Serial.begin(9600);
    Serial.pri

}

void move_servo_from_serial(Servo servo){
    /**
     * This function will read a value from the serial monitor (in the µs unit).
     * @param: servo - The servo motor
     */

    while(Serial.available()){
        if(Serial.available() > 0){
            char c = Serial.read(); // reading from the serial monitor
            strchr(read_string, c);
            delay(3);
        }
    }

    if(strlen(read_string) != 0){
        if(char_is_number(read_string) && 500 <= char_2_int(read_string) && char_2_int(read_string) <= 2500) {
            Serial.println(char_2_int(read_string));
            servo.writeMicroseconds(char_2_int(read_string)); // writing the string
            strcpy(read_string, "");
        } else{
            Serial.println("The input is not a valid value ! \n");
        }
    }
}

bool char_is_number(char num[23]){
    /**
     * Verifying if a string is a number.
     * @param: str - The array of chars.
     * @return: Returns if the str argument is a number.
     */

    for(int i = 0; i < strlen(num); i++){
        if(isdigit(num[i]) == false){
            return false;
        }
    }
    return true;
}

int char_2_int(char num[23]){
    /**
     * Transforming a variable from a char into a num.
     * @param num - The char.
     * @return Will return the number that was find in the char.
     */
    int number = 0;
    for(int i = 0; i < strlen(num); i++){
        number += num[i];
        number *= 10;
    }
    return number / 10;
}