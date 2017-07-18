#include <iostream>
#include <winsock2.h>
#include <vector>
#include <thread>

#pragma comment(lib,"ws2_32.lib")
class Client
{
	WSADATA WsaDat;
	SOCKET Socket;
	std::string serverName;
	int serverPort;

public:

	Client(std::string serverName, int serverPort);
	~Client();
	void connectToServer();
	char* receiveDataFromServer();
	void sendDataToServer(std::string data);
};

