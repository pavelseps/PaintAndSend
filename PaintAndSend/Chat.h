#include <iostream>
#include <string>
#include "Connection.h"

#pragma once
class Chat
{
	Connection* c;

public:
	Chat();
	~Chat();

	void sendMessage(std::string s);

};

