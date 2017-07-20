#include "stdafx.h"
#include "Gui.h"


Gui::Gui()
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Can't load font";
		return;
	}
}


Gui::~Gui()
{
}

std::thread Gui::startInThread() {
	return std::thread([this] { this->start(); });
}

void Gui::menu() {
	s.erase();

	//Focused input/button
	TextInput* focused = nullptr;
	TextLabel* clickedBtn = nullptr;

	//Focus text
	FocusCheck<TextInput>* focusTextInput = new FocusCheck<TextInput>();
	FocusCheck<TextLabel>* focusTextLabel = new FocusCheck<TextLabel>();

	//Text input
	TextInput* name = new TextInput(sf::Vector2f(10, 10), sf::Vector2f(340, 20), font);
	name->setLabel("Name");
	focusTextInput->setTextInput(name);

	TextInput* ip = new TextInput(sf::Vector2f(10, 100), sf::Vector2f(240, 20), font);
	ip->setLabel("Ip");
	focusTextInput->setTextInput(ip);

	TextInput* port = new TextInput(sf::Vector2f(260, 100), sf::Vector2f(80, 20), font);
	port->setLabel("Port");
	focusTextInput->setTextInput(port);

	TextInput* createServerPort = new TextInput(sf::Vector2f(10, 200), sf::Vector2f(80, 20), font);
	createServerPort->setLabel("Port");
	focusTextInput->setTextInput(createServerPort);


	//Buttons
	TextLabel* createServerBtn = new TextLabel(sf::Vector2f(230, 216), sf::Vector2f(110, 22), font);
	createServerBtn->setText("Start Server");
	createServerBtn->setBackgroundColor(sf::Color::Black);
	createServerBtn->setTextColor(sf::Color::White);
	createServerBtn->setId("startServer");
	focusTextLabel->setTextInput(createServerBtn);

	TextLabel* startClientBtn = new TextLabel(sf::Vector2f(230, 180), sf::Vector2f(110, 22), font);
	startClientBtn->setText("Star Client");
	startClientBtn->setBackgroundColor(sf::Color::Black);
	startClientBtn->setTextColor(sf::Color::White);
	startClientBtn->setId("startClient");
	focusTextLabel->setTextInput(startClientBtn);

	//Color list
	ColorList* colorlist = new ColorList(sf::Vector2f(20, 20), sf::Vector2f(10, 70), 5, 6);
	colorlist->addColor(sf::Color::Black);
	colorlist->addColor(sf::Color::Green);
	colorlist->addColor(sf::Color::Yellow);
	colorlist->addColor(sf::Color::Magenta);
	colorlist->addColor(sf::Color::Blue);
	colorlist->addColor(sf::Color::Cyan);

	sf::RenderWindow window(sf::VideoMode(370, 600), "Menu - Paint and Send");

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
						if(s.size()>0)
							s.erase(s.size() - 1);
						break;
					case 13: //Enter
						break;
					default:
						s.push_back(c);
						break;
					}
					std::cout << s << std::endl;
					if (focused != nullptr)
						focused->setText(s);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//get focused input
					focused = focusTextInput->checkFocus(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

					//reset all inputs border
					name->setBorderColor(sf::Color::Black);
					ip->setBorderColor(sf::Color::Black);
					port->setBorderColor(sf::Color::Black);
					createServerPort->setBorderColor(sf::Color::Black);

					//set up focused input
					if (focused != nullptr) {
						focused->setBorderColor(sf::Color::Green);
						s.erase();
					}

					//buttons
					clickedBtn = focusTextLabel->checkFocus(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
					if (clickedBtn != nullptr) {
						std::string id = clickedBtn->getId();

						if (id == "startServer") {
							std::string sPort = createServerPort->getText();

							if (sPort.size() > 0) {
								window.close();
								server = new Server(sPort);
								std::thread t1 = server->startLisseningInThread();
								t1.join();
							}
							else {
								createServerPort->setBorderColor(sf::Color::Red);
							}
						}
						else if (id == "startClient") {
							std::string userName = name->getText();
							std::string sIp = ip->getText();
							std::string sPort = port->getText();
							if (userName.size() > 0 && sIp.size() > 0 && sPort.size() > 0) {
								window.close();
								connection = new Connection(sIp, sPort);
								connection->setUserName(userName);
								connection->setColor(this->focusedColor);

								std::thread t1 = connection->listenServerInThread();
								std::thread t2 = this->startInThread();
								t1.join();
								t2.join();
							}
							else {
								name->setBorderColor(sf::Color::Red);
								ip->setBorderColor(sf::Color::Red);
								port->setBorderColor(sf::Color::Red);
							}
						}

						clickedBtn = nullptr;
					}

					//Color select
					if(colorlist->isSelected(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						focusedColor = colorlist->getSelected();
				}
			}
		}

		//Render all to screen
		window.clear(sf::Color::White);
		window.draw(*name);
		window.draw(*ip);
		window.draw(*port);
		window.draw(*startClientBtn);
		window.draw(*createServerPort);
		window.draw(*createServerBtn);
		window.draw(*colorlist);
		window.display();
	}
}


void Gui::start() {
	s.erase();
	actualLine.clear();

	sf::RenderWindow window(sf::VideoMode(1100, 600), "Chat - Paint and Send");

	sf::RectangleShape drawArea(sf::Vector2f(600, 596));
	drawArea.setFillColor(sf::Color::White);
	drawArea.setOutlineThickness(2);
	drawArea.setOutlineColor(sf::Color::Black);
	drawArea.setPosition(sf::Vector2f(2, 2));

	input.setFont(font);
	input.setFillColor(sf::Color::Black);
	input.setCharacterSize(20);
	input.setPosition(sf::Vector2f(650, 565));
	sf::RectangleShape textBorder(sf::Vector2f(400, 2));
	textBorder.setFillColor(sf::Color::Black);
	textBorder.setPosition(sf::Vector2f(650, 590));

	chat.setFont(font);
	chat.setFillColor(sf::Color::Black);
	chat.setCharacterSize(16);
	chat.setPosition(sf::Vector2f(650, 0));

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
					actualLine.append(sf::Vertex(sf::Vector2f(mouseX, mouseY), this->focusedColor));
				}
			}
		}
		
		//Check for new data
		std::pair<std::string, std::string> message = connection->getMessage();
		if (message.second != "") {
			chatString.append("\n");
			chatString.append(message.first + ": " + message.second);
			chat.setString(chatString);
		}

		std::pair<std::string, sf::VertexArray> line = connection->getLine();
		if(line.second.getVertexCount() > 0)
			lines[line.first].push_back(line.second);

		std::string deleteLine = connection->renderDeletedLine();
		if (deleteLine != "" && lines[deleteLine].size() > 0)
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