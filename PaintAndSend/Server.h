#include <iostream>
#include <string>
#include <list>
#include <thread>
#include <SFML/Network.hpp>

#pragma once
/*Server*/
class Server
{
	sf::TcpListener Listener;
	unsigned short port = 0;
public:
	Server(std::string sPort);
	~Server();

	/*Start listening client connections and messages*/
	void startLissening();

	/*Start listening client connections and messages in thread*/
	std::thread startLisseningInThread();
};