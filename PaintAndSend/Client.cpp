#include "stdafx.h"
#include "Client.h"


Client::Client(std::string serverName, int serverPort)
{
	// nastaveni serveru
	this->serverName = serverName;
	this->serverPort = serverPort;
	// inicializace winSock.dll
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		WSACleanup();
		throw std::string("Winsock error - Winsock initialization failed");
	}
	// vytvoreni sockety - IPv4 (AF_INET) zapouzdrujici TCP protokol (IPPROTO_TCP)
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		WSACleanup();
		throw std::string("Winsock error - Socket creation Failed!");
	}
}


Client::~Client()
{

	// uzavreni rozhrani
	shutdown(Socket, SD_SEND);
	// zruseni rozhrani
	closesocket(Socket);
	// vycisteni Winsock.dll
	WSACleanup();
}


void Client::connectToServer()
{
	// preklad jmena serveru na ip adresu
	struct hostent *host;
	if ((host = gethostbyname("localhost")) == NULL)
	{
		WSACleanup();
		throw std::string("Failed to resolve hostname.");
	}
	// nastaveni parametru sockety
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(serverPort);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	// pripojeni k serveru
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		WSACleanup();
		throw std::string("Failed to establish connection with server");
	}
}

char* Client::receiveDataFromServer()
{
	// zobrazeni zpravy od odesilatelne
	char buffer[1000];
	memset(buffer, 0, 999);
	int inDataLength = recv(Socket, buffer, 1000, 0);
	return buffer;
}

void Client::sendDataToServer(std::string data)
{
	send(Socket, data.c_str(), strlen(data.c_str()), 0);
}