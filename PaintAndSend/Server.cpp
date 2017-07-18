#include "stdafx.h"
#include "Server.h"



Server::Server() {

	/*if (Listener.listen(55001))
	{
		std::cout << "Listening" << std::endl;
	}
	else {
		std::cout << "Listener failed" << std::endl;
	}*/


	// Listen to the given port for incoming connections
	if (Listener.listen(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;
}

Server::~Server()
{
	
}

void Server::startLissening() {
	std::list<sf::TcpSocket*> clients;
	// Create a selector
	sf::SocketSelector selector;
	// Add the listener to the selector
	selector.add(Listener);

	while (true)
	{
		if (selector.wait())
		{
			if (selector.isReady(Listener))
			{

				sf::TcpSocket* client = new sf::TcpSocket;
				if (Listener.accept(*client) == sf::Socket::Done)
				{
					clients.push_back(client);
					selector.add(*client);
					std::cout << "Server added" << std::endl;
				}
				else
				{
					// Error, we won't get a new connection, delete the socket
					delete client;
				}
			}
			else
			{
				// The listener socket is not ready, test all other sockets (the clients)
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
				{
					sf::TcpSocket& client = **it;
					if (selector.isReady(client))
					{
						// The client has sent some data, we can receive it
						sf::Packet packet;
						if (client.receive(packet) == sf::Socket::Done)
						{
							for (std::list<sf::TcpSocket*>::iterator itin = clients.begin(); itin != clients.end(); ++itin) {
								sf::TcpSocket& clientin = **itin;
								if (clientin.send(packet) != sf::Socket::Done) {
									std::cout << "Error - send data to all clients" << std::endl;
									clients.erase(itin);
								}
								else {
									std::cout << "Message send to - " << clientin.getRemoteAddress() << ":" << clientin.getRemotePort() << std::endl;
								}
							}
						}
					}
				}
			}
		}
	}
}