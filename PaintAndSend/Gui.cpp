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
	connection->setUserName("Franta Lála");
	actualLine.clear();

	sf::RenderWindow window(sf::VideoMode(1100, 600), "Paint and Send");

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Can't load font";
		return;
	}

	sf::RectangleShape drawArea(sf::Vector2f(600, 596));
	drawArea.setFillColor(sf::Color::White);
	drawArea.setOutlineThickness(2);
	drawArea.setOutlineColor(sf::Color::Black);
	drawArea.setPosition(sf::Vector2f(2, 2));

	input.setFont(font);
	input.setFillColor(sf::Color::Black);
	input.setCharacterSize(20);
	input.setPosition(sf::Vector2f(650, 565));

	chat.setFont(font);
	chat.setFillColor(sf::Color::Black);
	chat.setCharacterSize(16);
	chat.setPosition(sf::Vector2f(650, 0));

	sf::RectangleShape textBorder(sf::Vector2f(400, 2));
	textBorder.setFillColor(sf::Color::Black);
	textBorder.setPosition(sf::Vector2f(650, 590));

	while (window.isOpen()) {

		//Event processing
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
					input.setString(s);
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

					//TODO: fix deleteting lines (problem with pair and pop_last()....)
					connection->deleteMyLine();
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					isDrawing = false;
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
		
		//Check for new data
		std::string message = connection->getMessage();
		if (message != "") {
			chatString.append("\n");
			chatString.append(message);
			chat.setString(chatString);
		}

		std::pair<std::string, sf::VertexArray> line = connection->getLine();
		if(line.second.getVertexCount() > 0)
			lines[line.first].push_back(line.second);

		std::string deleteLine = connection->renderDeletedLine();
		if (deleteLine != "")
			lines[deleteLine].pop_back();


		//Render all to screen
		window.clear(sf::Color::White);
		window.draw(input);
		window.draw(chat);
		window.draw(textBorder);
		window.draw(drawArea);
		window.draw(actualLine);
		for (auto const userLine : lines) {
			for (std::vector<int>::size_type i = 0; i != userLine.second.size(); i++) {
				window.draw(userLine.second[i]);
			}
		}
		window.display();
	}
}