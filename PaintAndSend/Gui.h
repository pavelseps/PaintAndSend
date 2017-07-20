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
class Gui
{
	std::map<std::string, std::vector<sf::VertexArray>> lines;
	sf::VertexArray actualLine = sf::VertexArray(sf::LineStrip);
	Connection* connection;
	Server* server;
	bool isDrawing = false;

	sf::Text input;
	sf::Font font;
	std::string s;

	sf::Color focusedColor = sf::Color::Black;

public:
	Gui();
	~Gui();

	void start();
	void menu();

	std::thread startInThread();
};