// PaintAndSend.cpp: Definuje vstupní bod pro konzolovou aplikaci.
//

#include "stdafx.h"
#include <iostream>
#include "Connection.h"
#include "Gui.h"


using namespace std;

int main()
{
	Gui* g = new Gui();
	g->menu();

    return 0;
}
