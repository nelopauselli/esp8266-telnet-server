#ifndef LED_OFF_COMMAND_CLASS
#define LED_OFF_COMMAND_CLASS

#include <Command.h>

class LedOffCommand : public Command
{
  public:
    LedOffCommand(int pin)
    {
        _pin = pin;
    }

    bool process(char *line, WiFiClient *socket) override
    {
        if (strcmp(line, "LED OFF") == 0)
        {
            digitalWrite(_pin, HIGH);
            socket->write("OK\r\n");
            delay(1);

            return true;
        }
        return false;
    }

    void help(WiFiClient *socket) override
    {
        socket->write("LED OFF: turn off a LED connect to pin ");
        socket->write(String(_pin).c_str());
        socket->write("\r\n");
    }

  private:
    int _pin;
};

#endif