#ifndef TELNET_SERVER_CLASS
#define TELNET_SERVER_CLASS

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Command.h"
#include "CommandListItem.h"

/**
 * Telnet Server 
 */
class TelnetServer
{
  public:
	TelnetServer(int port);

	void add(Command *command);
	void start();
	void process();

  private:
	WiFiServer *server = NULL;
	CommandListItem *commands = NULL;
	WiFiClient socket;
};

#endif