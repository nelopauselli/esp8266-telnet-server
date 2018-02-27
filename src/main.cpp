#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "TelnetServer.h"
#include "LedOnCommand.cpp"
#include "LedOffCommand.cpp"

const char* ssid     = "your-ssid";
const char* password = "your-password";

TelnetServer telnet(23);

void connectWifi()
{
    Serial.println("Conneting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        Serial.print(WiFi.status());
        Serial.print(" ");
    }

    Serial.print("Connection established with ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(115200);
    Serial.println("");

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    connectWifi();

    telnet.add(new LedOnCommand(LED_BUILTIN));
    telnet.add(new LedOffCommand(LED_BUILTIN));
    
    telnet.start();
}

void loop()
{
    telnet.process();
}