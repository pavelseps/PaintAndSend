#include <iostream>
#include <string>
#include <list>
#include <SFML/Network.hpp>

#pragma once
class Server
{
	sf::TcpListener Listener;
	const unsigned short port = 50001;
public:
	Server();
	~Server();

	void startLissening();

};

