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
	std::vector<std::string> messageBufferShow;
	std::vector<sf::VertexArray> lineBufferShow;
	std::string userName = "";
	const unsigned short port = 50001;

	void sendMessageToServer();

public:
	Connection();
	~Connection();

	void listenServer();
	std::thread listenServerInThread();
	void sendMessage(std::string message);
	void sendLine(sf::VertexArray line);

	std::string getMessage();
	sf::VertexArray getLine();

	void userName(std::string n);
};

