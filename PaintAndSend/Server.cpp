#include "stdafx.h"
#include "Server.h"



Server::Server(std::string sPort) {
	this->port = (short)stoi(sPort);
}

Server::~Server(){
	
}

std::thread Server::startLisseningInThread() {
	return std::thread([this] { this->startLissening(); });
}

void Server::startLissening() {
	

	if (Listener.listen(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

	std::list<sf::TcpSocket*> clients;
	sf::SocketSelector selector;
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
					delete client;
				}
			}
			else
			{
				for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
				{
					sf::TcpSocket& client = **it;
					if (selector.isReady(client))
					{
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