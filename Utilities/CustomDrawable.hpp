#ifndef CUSTOMDRAWABLE
#define CUSTOMDRAWABLE

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace sf
{
	class CustomDrawable : public sf::Drawable, public sf::Transformable
	{
		public:
			sf::Text text;
			sf::String string;
			sf::Font font;
			
			CustomDrawable();
			~CustomDrawable();
			
			void clear();
			
			void setFont(const sf::Font &font);
			
			float getWidth() const;
				
			float getHeight() const;
		
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif // CUSTOMDRAWABLE
