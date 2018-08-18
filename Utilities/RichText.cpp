#include "RichText.hpp"
#include "CustomText.hpp"
#include <vector>
#include <iostream>

namespace sf
{	
	RichText::RichText() : myCurrentColor(sf::Color::Black), mySizeUpdated(false), myPositionUpdated(false)
	{
		//noting needed to do;	
	}

	RichText::RichText(sf::Font &font)
	{
		RichText();
		myCurrentFont = font;
	}
	
	void RichText::setString(const sf::String &string)
	{
		clear();
		addString(string);
	}
	
	void RichText::setString(const sf::String &string, int startIndex, int endIndex)
	{
		clear(startIndex, endIndex);
		addString(string, startIndex);
		makeTextCollectionFromString();
	}
	
	void RichText::addString(const sf::String &string)
	{
		mySizeUpdated = false;
		myPositionUpdated = false;
		
		myTexts.push_back(sf::CustomText());
		
		sf::CustomText &text = myTexts.back();
		text.setCharacterSize(myCurrentCharacterSize);
		text.setFont(myCurrentFont);
		text.setStyle(myStyle);
		text.setFillColor(myCurrentColor);
		if (myCurrentBackgroundColor != NULL)
		{
			text.setBackGroundColor(*myCurrentBackgroundColor, (float)myHighestCharacterSize + 1);
		}
		text.setString(string);
		makeTextCollectionFromString();
	}
	
	void RichText::addString(const sf::String &string, int startIndex)
	{
		mySizeUpdated = false;
		myPositionUpdated = false;
		
		text_collection::iterator textObj = makeTextObjectAt(startIndex);
		textObj->setFillColor(myCurrentColor);
		textObj->setFont(myCurrentFont);
		textObj->setStyle(myStyle);
		textObj->setCharacterSize(myCurrentCharacterSize);
		if (myCurrentBackgroundColor != NULL)
			textObj->setBackGroundColor(*myCurrentBackgroundColor, (float)myHighestCharacterSize + 1);
		textObj->setString(string);
		makeTextCollectionFromString();
	}
	
	void RichText::removeString(int startIndex, int endIndex)
	{
		mySizeUpdated = false;
		myPositionUpdated = false;
		
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		
		for(text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			it->setString("");
		}
		makeTextCollectionFromString();
	}
	
	void RichText::setCharacterSize(unsigned int size)
	{
		if (size > myHighestCharacterSize)
			myHighestCharacterSize = size;
		myCurrentCharacterSize = size;
	}
	
	void RichText::setCharacterSize(unsigned int size, int startIndex, int endIndex)
	{		
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		
		for(text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			it->setCharacterSize(size);
			it->setBackGroundColor(*(it->getBackGroundColor()), (float)myHighestCharacterSize + 1);
		}
		
		if (size > myHighestCharacterSize)
			myHighestCharacterSize = size;
		
		makeTextCollectionFromString();
		
		mySizeUpdated = false;
		myPositionUpdated = false;
	}
	
	void RichText::setFont(const sf::Font &font)
	{
		myCurrentFont = font;
	}
	
	void RichText::setFont(const sf::Font &font, int startIndex, int endIndex)
	{
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		
		for(text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			it->setFont(font);
		}
		makeTextCollectionFromString();
		
		mySizeUpdated = false;
		myPositionUpdated = false;
	}

	void RichText::addStyle(Uint32 style)
	{
		bool add = true;
		for(unsigned int i = 0; i < myStyle.size(); i++)
		{
			if (myStyle[i] == style)
			{
				add = false;
			}
		}
		if (add) myStyle.push_back(style);
	}
	
	void RichText::addStyle(Uint32 style, int startIndex, int endIndex)
	{
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		
		for(text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			it->addStyle(style);
		}
		makeTextCollectionFromString();
		
		mySizeUpdated = false;
		myPositionUpdated = false;
	}
	
	void RichText::removeStyle(Uint32 style)
	{
		int removeIndex = 0;
		bool remove = false;
		for (unsigned int i = 0; i != myStyle.size(); ++i)
		{
			if (myStyle[i] == style)
			{
				remove = true;
				removeIndex = i;
			}
		}
		if (remove) myStyle.erase(myStyle.begin() + removeIndex);
	}
	
	void RichText::removeStyle(Uint32 style, int startIndex, int endIndex)
	{
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		
		for(text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			it->removeStyle(style);
		}
		
		makeTextCollectionFromString();
		
		mySizeUpdated = false;
		myPositionUpdated = false;
	}

	void RichText::setColor(const sf::Color &color)
	{
		myCurrentColor = color;
	}

	void RichText::setColor(const sf::Color &color, int startIndex, int endIndex)
	{
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		
		for(text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			it->setFillColor(color);
		}
		makeTextCollectionFromString();
		
		mySizeUpdated = false;
		myPositionUpdated = false;
	}
	
	void RichText::setBackGroundColor(const sf::Color &color)
	{
		myCurrentBackgroundColor = &color;
	}
	
	void RichText::setBackGroundColor(const sf::Color &color, int startIndex, int endIndex)
	{
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		
		for (text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			it->setBackGroundColor(color, (float)myHighestCharacterSize + 1);
		}
		makeTextCollectionFromString();
		
		mySizeUpdated = false;
		myPositionUpdated = false;
	}
	
	void RichText::clear()
	{
		myTexts.clear();
		mySize = sf::Vector2f(0.f, 0.f);
		
		mySizeUpdated = true;
		myPositionUpdated = true;
	}
	
	void RichText::clear(int startIndex, int endIndex)
	{
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		
		for (text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			it->setString("");
		}
		makeTextCollectionFromString();
		
		mySizeUpdated = false;
		myPositionUpdated = false;
	}
	
	const RichText::text_collection & RichText::getTextList() const
	{
		return myTexts;
	}
	
	unsigned int RichText::getCharacterSize() const
	{
		if(myTexts.size()) return myCurrentCharacterSize;
		return 0;
	}
	
	unsigned int RichText::getCharacterSize(int startIndex, int endIndex)
	{
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		bool sizeIsSame = true;
		unsigned int size;
		
		for (text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			text_collection::iterator itNext = it + 1;
			if (it->getCharacterSize() == itNext->getCharacterSize() && sizeIsSame)
			{
				size = it->getCharacterSize();
			} else {
				sizeIsSame = false;
				size = 0;
			}
		}
		
		return size;
	}
	
	const sf::Font* RichText::getFont() const
	{
		if(myTexts.size()) return myTexts.begin()->getFont();
		return &myCurrentFont;
	}
	
	const sf::Font* RichText::getFont(int startIndex, int endIndex)
	{
		text_obj_pair text_pair = getTextObjectFromTo(startIndex, endIndex + 1);
		bool fontIsSame = true;
		const sf::Font* font;
		
		for (text_collection::iterator it = text_pair.first; it != text_pair.second; ++it)
		{
			text_collection::iterator itNext = it + 1;
			if (it->getFont() == itNext->getFont() && fontIsSame)
			{
				font = it->getFont();
			} else {
				fontIsSame = false;
				font = NULL;
			}
		}
		
		return font;
	}
	
	float RichText::getWidth() const
	{
		updateSize();
		return mySize.x;
	}
	
	float RichText::getHeight() const
	{
		updateSize();
		return mySize.y;
	}
	
	//Draw
	void RichText::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		updatePosition();
		
		states.transform *= getTransform();
		
		for(text_collection::const_iterator it = myTexts.begin(); it != myTexts.end(); ++it)
		{
			bool isBold = false;
			for(unsigned int i = 0; i < it->getStyle().size(); i++)
			{
				if (it->getStyle()[i] == sf::CustomText::Bold)
				{
					isBold = true;
					break;
				}
			}
		
			float whitespaceWidth = it->getFont()->getGlyph(L' ', it->getCharacterSize(), isBold).advance;
			float letterSpacing   = ( whitespaceWidth / 3.f ) * ( it->getLetterSpacing() - 1.f );
			
			states.transform.translate(letterSpacing, 0);
			target.draw(*it, states);
		}
	}
	
	void RichText::updateSize() const
	{
		if (mySizeUpdated) return;
		
		if (myTexts.begin() == myTexts.end()) return;
		
		mySizeUpdated = true;
		
		mySize.x = 0.f;
		mySize.y = myTexts.begin()->getGlobalBounds().height;
		for(text_collection::const_iterator it = myTexts.begin(); it != myTexts.end(); ++it)
		{
			bool isBold = false;
			for(unsigned int i = 0; i < it->getStyle().size(); i++)
			{
				if (it->getStyle()[i] == sf::CustomText::Bold)
				{
					isBold = true;
					break;
				}
			}
		
			float whitespaceWidth = it->getFont()->getGlyph(L' ', it->getCharacterSize(), isBold).advance;
			float letterSpacing   = ( whitespaceWidth / 3.f ) * ( it->getLetterSpacing() - 1.f );
			
			mySize.x += it->getGlobalBounds().width + letterSpacing;
		}
	}
	
	void RichText::updatePosition() const
	{
		if (myPositionUpdated) return;
		if(myTexts.begin() == myTexts.end()) return;
		
		myPositionUpdated = true;
		
		sf::Vector2f offset;
		
		for(text_collection::iterator it = myTexts.begin(); it != myTexts.end(); ++it)
		{
			if (it->getCharacterSize() != myHighestCharacterSize)
			{
				unsigned int size = it->getCharacterSize();
				it->setCharacterSize(myHighestCharacterSize);
				sf::FloatRect bounds = it->getLocalBounds();
				it->setCharacterSize(size);
				float lineSpacing = it->getFont()->getLineSpacing(myHighestCharacterSize) * it->getLineSpacing();
				it->setOrigin(it->getOrigin().x, it->getPosition().y - ((bounds.top + bounds.height) - (it->getLocalBounds().top + it->getLocalBounds().height)));
			}
			
			it->setOrigin(it->getPosition().x - myTexts.begin()->getPosition().x - offset.x, it->getOrigin().y);
			
			bool isBold = false;
			for(unsigned int i = 0; i < it->getStyle().size(); i++)
			{
				if (it->getStyle()[i] == sf::CustomText::Bold)
				{
					isBold = true;
					break;
				}
			}
		
			float whitespaceWidth = it->getFont()->getGlyph(L' ', it->getCharacterSize(), isBold).advance;
			float letterSpacing   = ( whitespaceWidth / 3.f ) * ( it->getLetterSpacing() - 1.f );
			
			const sf::FloatRect rect = it->getGlobalBounds();
			offset.x += rect.width + letterSpacing;
		}
	}
	
	RichText::text_collection::iterator RichText::makeTextObjectAt(int pos)
	{	
		text_obj textObj = getTextObjectAt(pos);
		
		if (pos == 0)
		{
			return myTexts.insert(textObj.first, sf::CustomText());
		} else {
			int length = pos - textObj.second;
			text_collection::iterator it = textObj.first;
			sf::String subStrFore = it->getString().substring(0, length);
			sf::String subStrAfter = it->getString().substring(length, sf::String::InvalidPos);
			
			if (subStrFore != "")
			{
				makeTextObjectWithStringBefore(it, subStrFore);
			}
			if (subStrAfter != "")
			{
				if (it + 1 == myTexts.end())
				{
					addString(subStrAfter);
				} else
					makeTextObjectWithStringBefore(it + 1, subStrAfter);
			}
			
			return it;
		}
		
		//something's wrong
		return textObj.first;
	}
	
	RichText::text_collection::iterator RichText::makeTextObjectWithStringBefore(text_collection::iterator it, sf::String string)
	{
		text_collection::iterator obj = myTexts.insert(it, sf::CustomText(string, *(it->getFont()), it->getCharacterSize(), it->getFillColor(), it->getStyle()));
		obj->setBackGroundColor(*(it->getBackGroundColor()), (float)myHighestCharacterSize + 1);
		
		return obj;
	}
	
	RichText::text_obj RichText::getTextObjectAt(int pos) const
	{
		text_obj result = std::make_pair(myTexts.end(), 0);
		if (pos == 0)
		{
			result = std::make_pair(myTexts.begin(), 0);
		}
		
		int index = 0;
		
		for(text_collection::iterator it = myTexts.begin(); it != myTexts.end(); ++it)
		{
			if (index + it->getString().getSize() > ((unsigned int)pos))
			{
				return std::make_pair(it, index);
			}
			index += it->getString().getSize();
		}
		
		//something's wrong
		return result;
	}
	
	RichText::text_obj_pair RichText::getTextObjectFromTo(int fromIndex, int toIndex)
	{
		text_obj textStart = getTextObjectAt(fromIndex);
		
		int length = fromIndex - textStart.second;
		sf::String subStrBefore = textStart.first->getString().substring(0, length);
		textStart.first->setString(textStart.first->getString().substring(length, sf::String::InvalidPos));
		makeTextObjectWithStringBefore(textStart.first, subStrBefore);
		
		text_obj textEnd = getTextObjectAt(toIndex);
		
		int length2 = toIndex - textEnd.second;
		sf::String stringBefore = textEnd.first->getString().substring(0, length2);
		textEnd.first->setString(textEnd.first->getString().substring(length2, sf::String::InvalidPos));
		makeTextObjectWithStringBefore(textEnd.first, stringBefore);
		textEnd = getTextObjectAt(toIndex);
		textStart = getTextObjectAt(fromIndex);
		
		return std::make_pair(textStart.first, textEnd.first);
	}
	
	void RichText::makeTextCollectionFromString()
	{
		for (text_collection::iterator it = myTexts.begin(); it != myTexts.end(); it++)
		{
			while (it->getString() == "")
			{
				it = removeWhiteSpace(it);
			}
			text_collection::iterator itNext = it + 1;
			if (it->getFont() == itNext->getFont())
			{
				if (it->getCharacterSize() == itNext->getCharacterSize())
				{
					if (it->getFillColor() == itNext->getFillColor())
					{
						if (it->getStyle() == itNext->getStyle())
						{
							if (it->getBackGroundColor() == itNext->getBackGroundColor())
							{
								std::cout << "deleted" << std::endl;
								it->setString(it->getString() + itNext->getString());
								myTexts.erase(itNext);
							}
						}
					}
				}
			}
		}
	}
	
	RichText::text_collection::iterator RichText::removeWhiteSpace(text_collection::iterator it)
	{
		myTexts.erase(it);
		return myTexts.begin();
	}
	
}
