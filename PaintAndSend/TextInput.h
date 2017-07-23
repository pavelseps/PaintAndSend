#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
/*
Giu element using sfml
Generate bordered input text with label
*/
class TextInput : public sf::Drawable
{
	sf::Text label;
	sf::Text input;
	sf::RectangleShape border;
	int padding = 2;
	std::string text = "";

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	TextInput(sf::Vector2f &coords, sf::Vector2f &size, sf::Font &font);
	~TextInput();

	/*Set text*/
	void setText(std::string s);

	/*Get text*/
	std::string getText();

	/*Set border color*/
	void setBorderColor(sf::Color c);

	/*Set label string*/
	void setLabel(std::string s);

	/*Set positions*/
	void setCoords(sf::Vector2f &coords);

	/*Ser size*/
	void setSize(sf::Vector2f &size);

	/*Check if mose is on element and add to selectedColor*/
	bool isFocused(int mouseX, int mouseY);

	/*Check if is text escaping outside of border*/
	bool isTextEscaping() {
		return input.getLocalBounds().width + 20 > border.getSize().x;
	}
};