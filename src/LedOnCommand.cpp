#ifndef LED_ON_COMMAND_CLASS
#define LED_ON_COMMAND_CLASS

#include <Command.h>

class LedOnCommand : public Command
{
  public:
    LedOnCommand(int pin)
    {
        _pin = pin;
    }

    bool process(char *line, WiFiClient *socket) override
    {
        if (strcmp(line, "LED ON") == 0)
        {
            digitalWrite(_pin, LOW);
            socket->write("OK\r\n");
            delay(1);

            return true;
        }
        return false;
    }

    void help(WiFiClient *socket) override
    {
        socket->write("LED ON: turn on a LED connect to pin ");
        socket->write(String(_pin).c_str());
        socket->write("\r\n");
    }

  private:
    int _pin;
};

#endif