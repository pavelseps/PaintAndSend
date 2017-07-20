#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <SFML/Network.hpp>

#pragma once
class Server
{
	sf::TcpListener Listener;
	unsigned short port = 0;
public:
	Server(std::string sPort);
	~Server();

	void startLissening();
	std::thread startLisseningInThread();

};