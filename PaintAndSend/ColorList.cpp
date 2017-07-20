#include "stdafx.h"
#include "ColorList.h"


ColorList::ColorList(sf::Vector2f s, sf::Vector2f c, int g, int pR)
{
	this->size = s;
	this->coords = c;
	this->gap = g;
	this->perRow = pR;
}


ColorList::~ColorList()
{
}

void ColorList::addColor(sf::Color c) {
	sf::RectangleShape rec(this->size);
	rec.setFillColor(c);
	rec.setOutlineThickness(1);
	rec.setOutlineColor(sf::Color::Black);

	if (vec.size() > 0) {
		if (vec.size() % perRow == 0) {
			rec.setPosition(sf::Vector2f(coords.x, vec.back().getPosition().y + gap + size.y));
		}
		else {
			rec.setPosition(sf::Vector2f(vec.back().getPosition().x + gap + size.x, vec.back().getPosition().y));
		}
	}
	else {
		rec.setPosition(coords);
	}

	vec.push_back(rec);
}

bool ColorList::isSelected(int mouseX, int mouseY) {
	bool ret = false;

	for (int i = 0; i < vec.size(); i++) {
		if (mouseX > vec[i].getPosition().x && mouseY > vec[i].getPosition().y && mouseX < (vec[i].getSize().x + vec[i].getPosition().x) && mouseY < (vec[i].getSize().y + vec[i].getPosition().y)) {
			selectedColor = &vec[i];
			ret = true;
		}
	}

	if (ret) {
		for (int i = 0; i < vec.size(); i++)
			vec[i].setOutlineColor(sf::Color::Black);
		selectedColor->setOutlineColor(sf::Color::Green);
	}

	return ret;
}

sf::Color ColorList::getSelected() {
	return selectedColor->getFillColor();
}

void ColorList::resetSelected() {
	for (int i = 0; i < vec.size(); i++)
		vec[i].setOutlineColor(sf::Color::Black);
	this->selectedColor = nullptr;
}

void ColorList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (int i = 0; i < vec.size(); i++) {
		target.draw(vec[i], states);
	}
}