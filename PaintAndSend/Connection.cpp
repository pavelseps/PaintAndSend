#include "stdafx.h"
#include "Connection.h"

struct dataToSend {
	sf::Int8 type;
	std::string name;
	std::string message;
} data;

struct dataConst {
	sf::Int8 message = 1;
	sf::Int8 line = 2;
} dataConst;

sf::Packet& operator <<(sf::Packet& packet, const dataToSend& d)
{
	return packet << d.type << d.name << d.message;
}
sf::Packet& operator >>(sf::Packet& packet, dataToSend& d)
{
	return packet >> d.type >> d.name >> d.message;
}



Connection::Connection()
{
	sf::Socket::Status status = socket.connect("127.0.0.1", port);
	if (status == sf::Socket::Done)
	{
		std::cout << "Client: connected to server" << std::endl;
	}
	else {
		std::cout << "Client: connection failed" << std::endl;
		return;
	}
}


Connection::~Connection()
{
	socket.disconnect();
}

void Connection::listenServer() {
	socket.setBlocking(false);
	while (true) {
		this->sendMessageToServer();
		sf::Packet packet;
		if (socket.receive(packet) == sf::Socket::Done)
		{
			
			packet >> data;
			if (data.type == dataConst.message) {
				std::cout << "Got message from server: " << data.message << std::endl;
				messageBufferShow.push_back(data.name + ": " +  data.message);
			}
			else if (data.type == dataConst.line) {
				std::cout << "Got line from server..." << std::endl;

				sf::VertexArray line = sf::VertexArray(sf::LineStrip);
				std::stringstream sscoords(data.message);
				std::string segment;
				std::vector<std::string> coords;
				std::vector<std::string> coord;

				while (std::getline(sscoords, segment, ';'))
				{
					coords.push_back(segment);
				}

				for (int i = 0; i < coords.size(); i++) {
					std::stringstream sscoord(coords[i]);
					while (std::getline(sscoord, segment, ':'))
					{
						coord.push_back(segment);
					}

					line.append(sf::Vertex(sf::Vector2f(std::stof(coord[0]), std::stof(coord[1])), sf::Color::Black));
					coord.clear();
				}
				lineBufferShow.push_back(line);
			}
		}
	}
}

std::thread Connection::listenServerInThread() {
	return std::thread([this] { this->listenServer(); });
}


void Connection::sendMessage(std::string message) {
	if(message != "")
		messageBufferSend.push_back(message);
}

void Connection::sendLine(sf::VertexArray line) {
	if(line.getVertexCount() > 0)
		lineBufferSend.push_back(line);
}

void Connection::sendMessageToServer() {
	sf::Packet packet;

	if (messageBufferSend.size() > 0) {
		data.type = 1;
		data.message = messageBufferSend.back();
		data.name = userName;
		messageBufferSend.pop_back();
		packet << data;

		// TCP socket:
		if (socket.send(packet) == sf::Socket::Done)
		{
			std::cout << "Client: message send" << std::endl;
		}
		else {
			std::cout << "Client: message send failed" << std::endl;
			return;
		}
	}

	if (lineBufferSend.size() > 0) {

		std::string line = "";
		sf::VertexArray va = lineBufferSend.back();

		for (int unsigned i = 0; i < va.getVertexCount(); i++) {
			std::ostringstream ss;
			ss << va[i].position.x;
			line += ss.str() + ":";
			ss.str("");
			ss.clear();
			ss << va[i].position.y;
			line += ss.str() + ";";
		}
		lineBufferSend.pop_back();

		data.type = 2;
		data.message = line;
		data.name = userName;
		packet << data;

		if (socket.send(packet) == sf::Socket::Done)
		{
			std::cout << "Client: line send" << std::endl;
		}
		else {
			std::cout << "Client: line send failed" << std::endl;
			return;
		}
	}
}


std::string Connection::getMessage() {
	std::string ret = "";
	if (messageBufferShow.size() > 0) {
		ret = messageBufferShow.back();
		messageBufferShow.pop_back();
	}
	return ret;
}
sf::VertexArray Connection::getLine() {
	sf::VertexArray ret;
	if (lineBufferShow.size() > 0) {
		ret = lineBufferShow.back();
		lineBufferShow.pop_back();
	}
	return ret;
}

void Connection::userName(std::string n) {
	this->userName = n;
}