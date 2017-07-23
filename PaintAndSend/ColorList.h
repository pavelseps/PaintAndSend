#include <SFML/Graphics.hpp>
#include <vector>

#pragma once
/*
 Giu element using sfml
 For generating colored label
*/
class ColorList : public sf::Drawable
{
	sf::Vector2f size;
	sf::Vector2f coords;
	sf::RectangleShape* selectedColor = nullptr;

	int gap;
	int perRow;

	std::vector<sf::RectangleShape> vec;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	ColorList(sf::Vector2f &s, sf::Vector2f &c, int g, int pR);
	~ColorList();

	/*Add color to generate*/
	void addColor(sf::Color c);

	/*Check if mose is on element and add to selectedColor*/
	bool isSelected(int mouseX, int mouseY);

	/*Get selected color*/
	sf::Color getSelected();

	/*Reset selected color*/
	void resetSelected();
};

