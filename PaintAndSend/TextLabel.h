#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
/*
Giu element using sfml
Label with background and text
Mostly used like button
*/
class TextLabel : public sf::Drawable
{
	sf::Text input;
	sf::RectangleShape background;
	int padding = 3;
	std::string id = "";

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	TextLabel(sf::Vector2f &coords, sf::Vector2f &size, sf::Font &font);
	~TextLabel();

	/*Set text*/
	void setText(std::string s);

	/*Get text*/
	std::string getText();

	/*Set backgrround color*/
	void setBackgroundColor(sf::Color c);

	/*Set text color*/
	void setTextColor(sf::Color c);

	/*Set position*/
	void setCoords(sf::Vector2f &coords);

	/*Set size*/
	void setSize(sf::Vector2f &size);

	/*Check if mose is on element and add to selectedColor*/
	bool isFocused(int mouseX, int mouseY);

	/*Set id*/
	void setId(std::string s);

	/*Get id*/
	std::string getId();
};

