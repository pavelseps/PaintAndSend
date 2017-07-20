#include "Client.h"
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#pragma once
class Connection
{

	sf::TcpSocket socket;
	sf::TcpListener Listener;
	sf::SocketSelector selector;

	std::vector<std::string> messageBufferSend;
	std::vector<sf::VertexArray> lineBufferSend;

	std::vector<std::pair<std::string, std::string>> messageBufferShow;
	std::vector<std::pair<std::string, sf::VertexArray>> lineBufferShow;

	std::vector<std::string> lineBufferToDelete;
	std::string userName = "";
	std::string localPort = "";
	unsigned short port = 0;

	void sendMessageToServer();

public:
	Connection(std::string sIp, std::string sPort);
	~Connection();

	void listenServer();
	std::thread listenServerInThread();
	void sendMessage(std::string message);
	void sendLine(sf::VertexArray line);

	std::pair<std::string, std::string> getMessage();
	std::pair<std::string, sf::VertexArray> getLine();

	void setUserName(std::string n);
	std::string getUserName();

	void setLocalPort(std::string n);
	std::string getLocalPort();

	void deleteMyLine();
	std::string renderDeletedLine();
};

