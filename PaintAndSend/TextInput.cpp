#include "stdafx.h"
#include "TextInput.h"


TextInput::TextInput(sf::Vector2f coords, sf::Vector2f size, sf::Font &font)
{
	label.setFont(font);
	label.setFillColor(sf::Color::Black);
	label.setCharacterSize(12);
	label.setPosition(coords);
	label.setString("");
	
	input.setFont(font);
	input.setFillColor(sf::Color::Black);
	input.setCharacterSize(size.y-(padding*2));
	input.setPosition(sf::Vector2f(coords.x+padding, coords.y+16));
	input.setString("");

	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(1);
	border.setSize(size);
	border.setPosition(coords.x, coords.y + 15);
}


TextInput::~TextInput()
{
}


void TextInput::setText(std::string s) {
	input.setString(s);
}

std::string TextInput::getText() {
	return input.getString();
}

void TextInput::setBorderColor(sf::Color c) {
	border.setOutlineColor(c);
}

void TextInput::setLabel(std::string s) {
	label.setString(s);
}

void TextInput::setCoords(sf::Vector2f coords) {
	label.setPosition(coords);
	input.setPosition(sf::Vector2f(coords.x, coords.y + 15));;
	border.setPosition(coords.x, coords.y + 15);
}

void TextInput::setSize(sf::Vector2f size) {
	input.setCharacterSize(size.y);
	border.setSize(size);
}

void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(border, states);
	target.draw(label, states);
	target.draw(input, states);
}

bool TextInput::isFocused(int mouseX, int mouseY) {
	return mouseX > label.getPosition().x && mouseY > label.getPosition().y && mouseX < (border.getSize().x + border.getPosition().x) && mouseY < (border.getSize().y + border.getPosition().y);
}
