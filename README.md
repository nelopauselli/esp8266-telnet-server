# esp8266-telnet-server
A telnet server on esp8266

# Getting started
```cpp
#include "TelnetServer.h"

TelnetServer telnet(23);
void setup() {
    telnet.start();
}

void loop() 
    telnet.process();
}
```

# Add a custom command handler
```cpp
void setup() {
    telnet.add(new LedBuiltInOnCommand());
    telnet.start();
}
```

# Define a custom command handler (by example: turn on LED_BUILTIN)
```cpp
#include <Command.h>

class LedBuiltInOnCommand : public Command
{
  public:
    /**
     * try handle command
     */
    bool process(char *line, WiFiClient *socket) override
    {
        if (strcmp(line, "LED ON") == 0)
        {
            digitalWrite(LED_BUILTIN, LOW); // this led on with LOW
            socket->write("OK\r\n"); // send a 'OK' to client
            delay(1);

            return true; // return 'I've handled the command'
        }
        return false; //if command isn't 'LED ON' then try with next handler 
    }

    /**
     * Help about this command handler
     */
    void help(WiFiClient *socket) override
    {
        socket->write("LED ON: turn on LED_BUILTIN\r\n");
    }
}
```