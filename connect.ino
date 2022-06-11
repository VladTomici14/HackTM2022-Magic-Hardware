#include "ESP8266WiFi.h"

// ---------- network variables --------
const char* ssid = "HackTM";
const char* password = "backspacehack";

// --------- creating the web server ------
int port = 8888;
WiFiServer server(port);

void setup() {

    // ------- loading the serial ----------
    Serial.begin(9600);

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

void loop() {

}

void receive_from_server(){
    WiFiClient client = server.available();
    if (client) {
        if(client.connected()) {
            Serial.println("Client connected ! ");
        }

        while(client.connected()){
            while(client.available() > 0){
                // reading data from the connected client
                Serial.write(client.read());
            }
            // sending Data to connected client
            while(Serial.available() > 0) {
                client.write(Serial.read());
            }
        }

        client.stop();
        Serial.println("Client disconnected");
    }
}