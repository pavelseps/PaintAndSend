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
	
	//Start server
	if (Listener.listen(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening!" << std::endl
		<< "Public connection: " <<  sf::IpAddress::getPublicAddress() << ":" << port << std::endl
		<< "Local connection: " << sf::IpAddress::getLocalAddress() << ":" << port << std::endl
		<< "waiting for connections... " << std::endl << std::endl;

	std::list<sf::TcpSocket*> clients;
	sf::SocketSelector selector;
	selector.add(Listener);


	//Start listening
	while (true)
	{
		if (selector.wait())
		{
			if (selector.isReady(Listener))
			{

				sf::TcpSocket* client = new sf::TcpSocket;
				if (Listener.accept(*client) == sf::Socket::Done)
				{
					//new client
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
							//Server got new message from server
							std::cout << "Got message from " << client.getRemoteAddress() << ":" << client.getRemotePort() << std::endl;

							/*Server sending actual message to all clients*/
							for (std::list<sf::TcpSocket*>::iterator targetClientIt = clients.begin(); targetClientIt != clients.end();) {
								sf::TcpSocket& targetClient = **targetClientIt;

								if (targetClient.send(packet) != sf::Socket::Done) {
									//Server can't send message to client and removing client from list of connected clients
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