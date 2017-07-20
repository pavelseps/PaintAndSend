#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class TextLabel : public sf::Drawable
{
	sf::Text input;
	sf::RectangleShape background;
	int padding = 3;
	std::string id = "";

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	TextLabel(sf::Vector2f coords, sf::Vector2f size, sf::Font &font);
	~TextLabel();

	void setText(std::string s);
	std::string getText();

	void setBackgroundColor(sf::Color c);
	void setTextColor(sf::Color c);


	void setCoords(sf::Vector2f coords);
	void setSize(sf::Vector2f size);

	bool isFocused(int mouseX, int mouseY);

	void setId(std::string s);
	std::string getId();
};

