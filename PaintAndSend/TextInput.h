#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class TextInput : public sf::Drawable
{
	sf::Text label;
	sf::Text input;
	sf::RectangleShape border;
	int padding = 2;
	std::string text = "";

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	TextInput(sf::Vector2f coords, sf::Vector2f size, sf::Font &font);
	~TextInput();

	void setText(std::string s);
	std::string getText();

	void setBorderColor(sf::Color c);

	void setLabel(std::string s);

	void setCoords(sf::Vector2f coords);
	void setSize(sf::Vector2f size);

	bool isFocused(int mouseX, int mouseY);
};