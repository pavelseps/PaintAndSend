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
	std::vector<std::string> messageBuffer;
	std::vector<sf::VertexArray> lineBuffer;
	std::thread mainThread;
	const unsigned short port = 50001;
	const unsigned short portListen = 50002;

	void sendMessageToServer();

public:
	Connection();
	~Connection();

	void listenServer();
	std::thread listenServerInThread();
	void sendMessage(std::string message);
	void sendLine(sf::VertexArray line);
};

