#ifndef RICHTEXT_HPP
#define RICHTEXT_HPP

//Headers
#include "CustomText.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <vector>

namespace sf
{
	class RichText : public sf::Drawable, public sf::Transformable
	{
		public:
			typedef std::vector<sf::CustomText> text_collection;
			typedef std::pair<text_collection::iterator, int> text_obj;
			typedef std::pair<text_collection::iterator, text_collection::iterator> text_obj_pair;
			
			RichText();
			RichText(sf::Font &font);
			
			void setString(const sf::String &string);
			
			void setString(const sf::String &string, int startIndex, int endIndex);
			
			void addString(const sf::String &string);
			
			void addString(const sf::String &string, int startIndex);
			
			void removeString(int startIndex, int endIndex);
			
			void setCharacterSize(unsigned int size);
			
			void setCharacterSize(unsigned int size, int startIndex, int endIndex);
			
			void setFont(const sf::Font &font);
			
			void setFont(const sf::Font &font, int startIndex, int endIndex);
			
			void addStyle(Uint32 style);
			
			void addStyle(Uint32 style, int startIndex, int endIndex);
			
			void removeStyle(Uint32 style);
			
			void removeStyle(Uint32 style, int startIndex, int endIndex);
			
			void setColor(const sf::Color &color);
			
			void setColor(const sf::Color &color, int startIndex, int endIndex);
			
			void setBackGroundColor(const sf::Color &color);
			
			void setBackGroundColor(const sf::Color &color, int startIndex, int endIndex);
			
			void getBackGroundColor();																											//not done
			
			void getBackGroundColor(int startIndex, int endIndex);													//not done
			
			void clear();
			
			void clear(int startIndex, int endIndex);
			
			const text_collection &getTextList() const;
			
			unsigned int getCharacterSize() const;
			
			unsigned int getCharacterSize(int startIndex, int endIndex);
			
			const sf::Font* getFont() const;
			
			const sf::Font* getFont(int startIndex, int endIndex);
			
			float getWidth() const;
			
			float getHeight() const;
			
		private:
			void updateSize() const;
			
			void updatePosition() const;

			void makeTextCollectionFromString();
			
			text_obj getTextObjectAt(int pos) const;
			
			text_obj_pair getTextObjectFromTo(int fromIndex, int toIndex);
			
			text_collection::iterator makeTextObjectAt(int pos);
			
			text_collection::iterator makeTextObjectWithStringBefore(text_collection::iterator it, sf::String string);
			
			text_collection::iterator removeWhiteSpace(text_collection::iterator it);
			
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			//Member data
			mutable text_collection myTexts;
			sf::Color myCurrentColor;
			const sf::Color* myCurrentBackgroundColor;
			sf::Font myCurrentFont;
			mutable sf::CustomText::style_collection myStyle;
			mutable unsigned int myHighestCharacterSize = 0;
			mutable unsigned int myCurrentCharacterSize;
			mutable sf::Vector2f mySize;
			mutable bool mySizeUpdated;
			mutable bool myPositionUpdated;
	};
}

#endif //RICHTEXT_HPP
