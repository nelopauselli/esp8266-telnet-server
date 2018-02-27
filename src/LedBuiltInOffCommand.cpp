#ifndef LED_BUILTIN_OFF_COMMAND_CLASS
#define LED_BUILTIN_OFF_COMMAND_CLASS

#include <Command.h>

class LedBuiltInOffCommand : public Command
{
  public:
    /**
     * try handle command
     */
    bool process(char *line, WiFiClient *socket) override
    {
        if (strcmp(line, "LED BUILTIN OFF") == 0)
        {
            digitalWrite(LED_BUILTIN, HIGH); // turn off the LED
            socket->write("OK\r\n"); // send a 'OK' to client
            delay(1);

            return true; // return 'I've handled the command'
        }
        return false; //if command isn't 'LED BUILTIN OFF' then try with next handler 
    }

    /**
     * Help about this command handler
     */
    void help(WiFiClient *socket) override
    {
        socket->write("LED BUILTIN OFF: turn off LED_BUILTIN\r\n");
    }
};

#endif