#ifndef LED_ON_COMMAND_CLASS
#define LED_ON_COMMAND_CLASS

#include "Command.h"
#include "CommandListItem.h"

class HelpCommand : public Command
{
  public:
    HelpCommand(CommandListItem *commands)
    {
        _commands = commands;
    }

    bool process(char *line, WiFiClient *socket) override
    {
        if (strcmp(line, "HELP") == 0)
        {
            Serial.println("Processing HELP");

            socket->write("COMMANDS:\r\n");

            CommandListItem *item = _commands;

            int index = 0;
            while (item != NULL)
            {
                Serial.println(index++);

                Command *command = item->command;
                command->help(socket);

                item = item->next;
            }
            socket->write("\r\n");

            return true;
        }
        return false;
    }

    void help(WiFiClient *socket) override
    {
        socket->write("HELP: show this help\r\n");
    }

  private:
    CommandListItem *_commands;
};

#endif