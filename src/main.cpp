#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "TelnetServer.h"
#include "LedBuiltInOnCommand.cpp"
#include "LedBuiltInOffCommand.cpp"

const char *ssid = "your-ssid";
const char *password = "your-password";

// Instanciating a telnet server on port 23
#define PORT 23
TelnetServer telnet(PORT);

bool connectWifi()
{
    Serial.println("Conneting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 20)
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Timeout. Connection fail :(");
        return false;
    }

    Serial.println("Connection established.");
    Serial.print("Open a telnet client as Putty in Windows and connect to ");
    Serial.print(WiFi.localIP());
    Serial.print(" on port ");
    Serial.println(PORT);

    return true;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("");

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    if (connectWifi())
    {
        // adding sample command handlers
        telnet.add(new LedBuiltInOnCommand());
        telnet.add(new LedBuiltInOffCommand());

        // starting the server
        telnet.start();
    }
}

void loop()
{
    telnet.process();
}