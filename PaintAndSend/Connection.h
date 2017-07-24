#include "Chat.h"
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#pragma once
/*Connect client to server*/
class Connection
{

	sf::TcpSocket socket;
	sf::SocketSelector selector;

	sf::Color selectedColor;

	std::vector<std::string> messageBufferSend;
	std::vector<sf::VertexArray> lineBufferSend;

	std::vector<GuiMessage> messageBufferShow;
	std::vector<std::pair<std::string, sf::VertexArray>> lineBufferShow;

	std::vector<std::string> lineBufferToDelete;
	std::string userName = "";
	std::string localPort = "";
	unsigned short port = 0;

	/*Send message from buffer to server*/
	void sendMessageToServer();

	sf::Socket::Status status;

public:
	Connection(std::string sIp, std::string sPort);
	~Connection();

	/*Listen sockets from server*/
	void listenServer();

	/*Start listenServer() in thread*/
	std::thread listenServerInThread();

	/*Send message to server*/
	void sendMessage(std::string message);

	/*Send line to server*/
	void sendLine(sf::VertexArray &line);

	/*Get new message from server*/
	GuiMessage getMessage();

	/*Get new line from server and id of user which draw line (id pattern is name_port)*/
	std::pair<std::string, sf::VertexArray> getLine();

	/*Set username*/
	void setUserName(std::string n);

	/*Get username*/
	std::string getUserName();

	/*Set local port*/
	void setLocalPort(std::string n);

	/*Get local port*/
	std::string getLocalPort();

	/*Delete user last line*/
	void deleteMyLine();

	/*Get new deleted line from server*/
	std::string renderDeletedLine();

	/*Set color which using user*/
	void setColor(sf::Color c);

	/*Get connection status*/
	sf::Socket::Status getStatus();

	bool isNewMessage();
};

