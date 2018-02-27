# esp8266-telnet-server
A telnet server on esp8266 open to extend the commands

_This code was written using [PlatformIO](https://platformio.org/) and [vscode](https://code.visualstudio.com/). Would you like the code as Arduino IDE friendly?... tell me!_

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
    // we should add all command handlers before start method invoked
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
        if (strcmp(line, "LED BUILTIN ON") == 0)
        {
            digitalWrite(LED_BUILTIN, LOW); // this led on with LOW
            socket->write("OK\r\n"); // send a 'OK' to client
            delay(1);

            return true; // return 'I've handled the command'
        }
        return false; //if command isn't 'LED BUILTIN ON' then try with next handler 
    }

    /**
     * Help about this command handler
     */
    void help(WiFiClient *socket) override
    {
        socket->write("LED BUILTIN ON: turn on LED_BUILTIN\r\n");
    }
};
```

# Telnet client
##  When connection is success
![PuTTY console](https://github.com/nelopauselli/esp8266-telnet-server/raw/master/doc/putty-1.png  "On connect")

## When commands are executed
![PuTTY console](https://github.com/nelopauselli/esp8266-telnet-server/raw/master/doc/putty-4.png  "On connect")
