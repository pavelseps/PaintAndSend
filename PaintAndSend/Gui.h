#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Connection.h"

#pragma once
class Gui
{
	std::map<std::string, std::vector<sf::VertexArray>> lines;
	sf::VertexArray actualLine = sf::VertexArray(sf::LineStrip);
	Connection* connection = new Connection();
	bool isDrawing = false;

	sf::Text input;
	sf::Text chat;
	std::string chatString;
	sf::Font font;
	std::string s;

public:
	Gui();
	~Gui();

	void start();

	std::thread startInThread();
};