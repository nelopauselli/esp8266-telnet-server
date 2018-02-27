#include <TelnetServer.h>

#include "Commands/PingPongCommand.cpp"
#include "Commands/NotFoundCommand.cpp"
#include "Commands/HelpCommand.cpp"

TelnetServer::TelnetServer(int port)
{
    server = new WiFiServer(port);
    server->begin();
    server->setNoDelay(true);

    add(new PingPongCommand());
}

void TelnetServer::add(Command *command)
{
    if (commands == NULL)
        commands = new CommandListItem(command);
    else
    {
        CommandListItem *item = commands;
        while (item->next != NULL)
        {
            item = item->next;
        }
        item->next = new CommandListItem(command);
    }
}

void TelnetServer::start()
{
    add(new HelpCommand(commands));
    add(new NotFoundCommand());

    Serial.println("Telnet is ready!");
}

void TelnetServer::process()
{
    //check if there are any new clients
    if (server->hasClient())
    {
        //find free/disconnected spot
        if (!socket || !socket.connected())
        {
            if (socket)
                socket.stop();
            socket = server->available();

            socket.write("\r\n");
            socket.write("####### ####### #       #     # ####### #######                      \r\n");
            socket.write("    #    #       #       ##    # #          #           ####  #    # \r\n");
            socket.write("    #    #       #       # #   # #          #          #    # ##   # \r\n");
            socket.write("    #    #####   #       #  #  # #####      #          #    # # #  # \r\n");
            socket.write("    #    #       #       #   # # #          #          #    # #  # # \r\n");
            socket.write("    #    #       #       #    ## #          #          #    # #   ## \r\n");
            socket.write("    #    ####### ####### #     # #######    #           ####  #    # \r\n");
            socket.write("\r\n");
            socket.write("    #######  #####  ######   #####   #####   #####   #####  \r\n");
            socket.write("    #       #     # #     # #     # #     # #     # #     # \r\n");
            socket.write("    #       #       #     # #     #       # #       #       \r\n");
            socket.write("    #####    #####  ######   #####   #####  ######  ######  \r\n");
            socket.write("    #             # #       #     # #       #     # #     # \r\n");
            socket.write("    #       #     # #       #     # #       #     # #     # \r\n");
            socket.write("    #######  #####  #        #####  #######  #####   #####  \r\n");
            socket.write("\r\n");
            socket.write("$ ");

            // Clean input stream
            while (socket.available())
            {
                socket.read();
            }
        }
        else
        {
            //no free/disconnected spot so reject
            WiFiClient other = server->available();
            other.write("Connection rejected");
            other.stop();
        }
    }

    //check clients for data
    if (socket && socket.connected())
    {
        if (socket.available())
        {
            //get data from the client until '\n' (and skip '\r')
            int bufferIndex = 0;
            char buffer[50];

            while (socket.available())
            {
                char c = socket.read();
                if (c == '\r')
                {
                    // no hacemos nada con este caracter
                }
                else if (c == '\n')
                {
                    // Fin de línea para la instrucción
                    break;
                }
                else
                {
                    // vamos acumulando los caracteres de la instrucción
                    buffer[bufferIndex++] = c;
                }
            }

            buffer[bufferIndex] = '\0';
            Serial.println(buffer);

            if (strlen(buffer) > 0)
            {
                CommandListItem *item = commands;
                while (item != NULL)
                {
                    Command *command = item->command;
                    if (command != NULL)
                    {
                        if (command->process(buffer, &socket))
                        {
                            break;
                        }
                    }
                    item = item->next;
                }

                socket.write("$ ");
            }
        }
    }
}