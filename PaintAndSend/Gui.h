#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Connection.h"
#include "Server.h"
#include "Chat.h"
#include "TextInput.h"
#include "TextLabel.h"
#include "ColorList.h"
#include "FocusCheck.h"

#pragma once
/*Giu*/
class Gui
{
	std::map<std::string, std::vector<sf::VertexArray>> lines;
	sf::VertexArray actualLine = sf::VertexArray(sf::LineStrip);
	Connection* connection;
	Server* server;

	sf::Font font;

	bool isDrawing = false;
	std::string inputText;

	sf::Color focusedColor = sf::Color::Black;

public:
	Gui();
	~Gui();

	/*Start menu*/
	void menu();

	/*Start client*/
	void start();

	/*Start client in thread*/
	std::thread startInThread();
};