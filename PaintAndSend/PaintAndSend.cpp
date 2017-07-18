// PaintAndSend.cpp: Definuje vstupní bod pro konzolovou aplikaci.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include "Server.h"
#include "Connection.h"
#include "Gui.h"


using namespace std;

int main()
{

	char c;
	std::cout << "Server (s) OR Client (c)?" << std::endl;
	std::cin >> c;
	if (c == 's') {
		//Star server
		Server* s = new Server();
		s->startLissening();
	}
	else {
		//Star GUI
		Gui* g = new Gui();
		g->start();
	}

	system("PAUSE");
    return 0;
}
