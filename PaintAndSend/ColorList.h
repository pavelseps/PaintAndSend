#include <SFML/Graphics.hpp>
#include <vector>

#pragma once
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
	ColorList(sf::Vector2f s, sf::Vector2f c, int g, int pR);
	~ColorList();


	void addColor(sf::Color c);

	bool isSelected(int mouseX, int mouseY);
	sf::Color getSelected();
	void resetSelected();
};

