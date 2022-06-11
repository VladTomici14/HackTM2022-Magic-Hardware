#include "ESP8266WiFi.h"
#include "WEMOS_Motor.h"

// ------ output variables -----
const int relay_pin = D1;
const int motor_pin = D8;

// ------- motor variables ------
int pwm;
int previous_position = 2;
Motor M1(0x30, _MOTOR_A, 1000);
Motor M2(0x30, _MOTOR_B, 1000);

// ---------- network variables --------
const char* ssid = "HackTM";
const char* password = "backspacehack";

// --------- creating the web server ------
int port = 8888;
WiFiServer server(port);

void setup() {
    // ------ initializing the serial -----
    Serial.begin(9600);

    // ------ setting up the relay ------
    pinMode(relay_pin, OUTPUT);

    // ------------ connecting to wifi ----------
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.print("Successfully connected to ");
    Serial.println(ssid);
    Serial.print(" !")

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // ------- starting the server -----
    server.begin();
    Serial.println("Listening on port 8888....");
}

// -------- relay functions -------
void turnOnRelay() { digitalWrite(relay_pin, HIGH); }
void turnOffRelay() { digitalWrite(relay_pin, LOW); }

// -------- motor functions ------
void rotate_left() { M1.setmotor(_CW, 100); }
void rotate_right() { M1.setmotor(_CCW, 100); }
void stop_motor() { M1.setmotor(_STOP); }

void move_wheel(int target_position, int previous_position){
    int range = target_position - previous_position;
    if(range < 0){
        rotate_left();
        delay(100 * -1 * range);
        stop_motor();
    } else{
        rotate_right();
        delay(100 * range);
        stop_motor();
    }
}

void loop() {

    // ------ reading data from the server -----
    WiFiClient client = server.available();
    if (client && client.connected()) {
        Serial.println("Client connected ! ");
        while (client.connected()) {
            // ------- reading from the server ------
            while (client.available() > 0) {
                Serial.write(client.read());
                int target_position = (int)client.read() - 48;
                move_wheel(target_position, previous_position);
                previous_position = target_position;
            }
            // ----- sending data to connected client ------
//            while (Serial.available() > 0) {
//                client.write(Serial.read());
//            }
        }
    }

    client.stop();
    Serial.println("Client disconnected");
}