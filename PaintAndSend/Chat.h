#include <SFML/Graphics.hpp>
#include <vector>

struct GuiMessage {
	sf::Color color;
	std::string name;
	std::string message;
};

#pragma once
/*
Giu element using sfml
generating chat element which displaing name, color and message
*/
class Chat : public sf::Drawable
{
	sf::Font font;
	std::vector<std::pair<sf::Text, sf::Text>*>& messages = std::vector<std::pair<sf::Text, sf::Text>*>();
	sf::Vector2f coords;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Chat(sf::Vector2f &coords, sf::Font &font);
	~Chat();

	/*Add message to chat*/
	void addMessage(GuiMessage &message);

	/*Remove all messages*/
	void clearChat();
};