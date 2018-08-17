#include "CustomDrawable.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

namespace sf
{
	CustomDrawable::CustomDrawable()
	{
		text = sf::Text();
		text.setString("Test");
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(25);
	}
	
	CustomDrawable::~CustomDrawable()
	{
		// do nothing
	}
	
	void CustomDrawable::clear()
	{
		text.setString("");
	}
	
	void CustomDrawable::setFont(const sf::Font &font)
	{
		text.setFont(font);
	}
	
	void CustomDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text);
	}
}
