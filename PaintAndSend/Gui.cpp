#include "stdafx.h"
#include "Gui.h"


Gui::Gui()
{

	std::thread t1 = connection->listenServerInThread();
	std::thread t2 = this->startInThread();

	t1.join();
	t2.join();
}


Gui::~Gui()
{
}

std::thread Gui::startInThread() {
	return std::thread([this] { this->start(); });
}


void Gui::start() {
	actualLine.clear();

	sf::RenderWindow window(sf::VideoMode(1100, 600), "Paint and Send");

	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	sf::RectangleShape drawArea(sf::Vector2f(600, 596));
	drawArea.setFillColor(sf::Color::White);
	drawArea.setOutlineThickness(2);
	drawArea.setOutlineColor(sf::Color::Black);
	drawArea.setPosition(sf::Vector2f(2, 2));

	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setPosition(sf::Vector2f(650, 0));

	sf::RectangleShape textBorder(sf::Vector2f(400, 1));
	textBorder.setFillColor(sf::Color::Black);
	textBorder.setPosition(sf::Vector2f(650, 25));

	while (window.isOpen()) {

		//Event processing.
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) {
					char c = (char)event.text.unicode;
					switch (c)
					{
					case 8: //Backspace
						s.erase(s.size() - 1);
						break;
					case 13: //Enter
						connection->sendMessage(s);
						s.erase();
						break;
					default:
						if (s.size() < 25)
							s.push_back(c);
						break;
					}
					text.setString(s);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					isDrawing = true;
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					if (lines.size() > 0)
						lines.pop_back();
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					isDrawing = false;
					//lines.push_back(actualLine);
					connection->sendLine(actualLine);
					actualLine.clear();
				}
			}
			if (event.type == sf::Event::MouseMoved) {
				int mouseX = sf::Mouse::getPosition(window).x;
				int mouseY = sf::Mouse::getPosition(window).y;
				if (isDrawing && mouseX > drawArea.getPosition().x && mouseY > drawArea.getPosition().y && mouseX < drawArea.getSize().x && mouseY < drawArea.getSize().y) {
					actualLine.append(sf::Vertex(sf::Vector2f(mouseX, mouseY), sf::Color::Black));
				}
			}
		}

		window.clear(sf::Color::White);
		window.draw(text);
		window.draw(textBorder);
		window.draw(drawArea);
		window.draw(actualLine);
		for (std::vector<int>::size_type i = 0; i != lines.size(); i++)
			window.draw(lines[i]);
		window.display();
	}
}