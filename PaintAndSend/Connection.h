#include "Chat.h"
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#pragma once
class Connection
{

	sf::TcpSocket socket;
	sf::SocketSelector selector;

	sf::Color selectedColor;

	std::vector<std::string> messageBufferSend;
	std::vector<sf::VertexArray> lineBufferSend;

	std::vector<GuiMessage*> messageBufferShow;
	std::vector<std::pair<std::string, sf::VertexArray>> lineBufferShow;

	std::vector<std::string> lineBufferToDelete;
	std::string userName = "";
	std::string localPort = "";
	unsigned short port = 0;

	void sendMessageToServer();

	sf::Socket::Status status;

public:
	Connection(std::string sIp, std::string sPort);
	~Connection();

	void listenServer();
	std::thread listenServerInThread();
	void sendMessage(std::string message);
	void sendLine(sf::VertexArray line);

	GuiMessage* getMessage();
	std::pair<std::string, sf::VertexArray> getLine();

	void setUserName(std::string n);
	std::string getUserName();

	void setLocalPort(std::string n);
	std::string getLocalPort();

	void deleteMyLine();
	std::string renderDeletedLine();

	void setColor(sf::Color c);

	sf::Socket::Status getStatus();
};

