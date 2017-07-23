#include "stdafx.h"
#include "TextLabel.h"


TextLabel::TextLabel(sf::Vector2f &coords, sf::Vector2f &size, sf::Font &font)
{
	input.setFont(font);
	input.setFillColor(sf::Color::Black);
	input.setCharacterSize(size.y - (padding * 2));
	input.setPosition(sf::Vector2f(coords.x + padding, coords.y + padding - 2));
	input.setString("");

	background.setFillColor(sf::Color::Black);
	background.setSize(size);
	background.setPosition(coords);
}


TextLabel::~TextLabel()
{
}

void TextLabel::setText(std::string s) {
	input.setString(s);
}

std::string TextLabel::getText() {
	return input.getString();
}

void TextLabel::setBackgroundColor(sf::Color c) {
	background.setFillColor(c);
}

void TextLabel::setTextColor(sf::Color c) {
	input.setFillColor(c);
}

void TextLabel::setCoords(sf::Vector2f &coords) {
	input.setPosition(sf::Vector2f(coords.x, coords.y + 15));;
	background.setPosition(coords.x, coords.y + 15);
}

void TextLabel::setSize(sf::Vector2f &size) {
	input.setCharacterSize(size.y);
	background.setSize(size);
}

bool TextLabel::isFocused(int mouseX, int mouseY) {
	return mouseX > background.getPosition().x && mouseY > background.getPosition().y && mouseX < (background.getSize().x + background.getPosition().x) && mouseY < (background.getSize().y + background.getPosition().y);
}

void TextLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(background, states);
	target.draw(input, states);
}

void TextLabel::setId(std::string s) {
	this->id = s;
}

std::string TextLabel::getId() {
	return this->id;
}