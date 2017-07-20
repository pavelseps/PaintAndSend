#include "stdafx.h"
#include "Chat.h"


Chat::Chat(sf::Vector2f coords, sf::Font &font)
{
	this->font = font;
	this->coords = coords;
}


Chat::~Chat()
{
}

void Chat::addMessage(GuiMessage &message) {
	std::pair<sf::Text, sf::Text>* pair = new std::pair<sf::Text, sf::Text>();
	pair->first = sf::Text();
	pair->first.setFont(font);
	pair->first.setFillColor(message.color);
	pair->first.setCharacterSize(16);
	pair->first.setString(message.name);

	pair->second = sf::Text();
	pair->second.setFont(font);
	pair->second.setFillColor(sf::Color::Black);
	pair->second.setCharacterSize(16);
	pair->second.setString(message.message);
	messages.push_back(pair);

	int messageSize = messages.size();
	for (int i = 0; i < messageSize; i++) {
		float posY = coords.y - ((messageSize - i) * 25);
		messages[i]->first.setPosition(sf::Vector2f(coords.x, posY));
		messages[i]->second.setPosition(sf::Vector2f(coords.x + 50, posY));
	}
}

void Chat::clearChat() {
	messages.clear();
}

void Chat::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	while (messages.size() > 0 && messages.front()->first.getPosition().y < 0) {
		messages.erase(messages.begin());
	}

	for (int i = 0; i < messages.size(); i++) {
		target.draw(messages[i]->first, states);
		target.draw(messages[i]->second, states);
	}
}