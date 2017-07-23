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
	std::cout << "Server is listening!" << std::endl
		<< "Public connection: " <<  sf::IpAddress::getPublicAddress() << ":" << port << std::endl
		<< "Local connection: " << sf::IpAddress::getLocalAddress() << ":" << port << std::endl
		<< "waiting for connections... " << std::endl << std::endl;

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
					std::cout << "New client connected" << std::endl;
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
							std::cout << "Got message from " << client.getRemoteAddress() << ":" << client.getRemotePort() << std::endl;

							for (std::list<sf::TcpSocket*>::iterator targetClientIt = clients.begin(); targetClientIt != clients.end();) {
								sf::TcpSocket& targetClient = **targetClientIt;

								if (targetClient.send(packet) != sf::Socket::Done) {
									std::cout << "Client " << targetClient.getRemoteAddress() << ":" << targetClient.getRemotePort() << " lost connection" << std::endl;
									targetClientIt = clients.erase(targetClientIt);
								}
								else {
									++targetClientIt;
								}
							}
						}
					}
				}
			}
		}
	}
}