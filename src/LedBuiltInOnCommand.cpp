#ifndef LED_BUILTIN_ON_COMMAND_CLASS
#define LED_BUILTIN_ON_COMMAND_CLASS

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

#endif