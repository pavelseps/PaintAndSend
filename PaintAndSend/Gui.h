#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Connection.h"

#pragma once
class Gui
{
	std::vector<sf::VertexArray> lines;
	sf::VertexArray actualLine = sf::VertexArray(sf::LineStrip);
	Connection* connection = new Connection();
	bool isDrawing = false;

	sf::Text text;
	sf::Font font;
	std::string s;

public:
	Gui();
	~Gui();

	void start();

	std::thread startInThread();
};
