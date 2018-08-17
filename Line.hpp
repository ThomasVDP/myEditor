#ifndef LINE_HPP
#define LINE_HPP

#include "RichText.hpp"
#include <SFML/Graphics.hpp>

namespace sf
{
	class TextLine {
		public:
			TextLine();
			TextLine(sf::RichText richText);
			TextLine(sf::String stringText);
			
			sf::RichText getText() const;
			
			void draw(float y);
			
		private:
			sf::RichText text;
	};
}

#endif //LINE_HPP
