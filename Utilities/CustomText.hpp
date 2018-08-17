#ifndef CUSTOM_TEXT_HPP
#define CUSTOM_TEXT_HPP

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/String.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace sf
{
	class SFML_GRAPHICS_API CustomText : public Drawable, public Transformable
	{
		public:
			typedef std::vector<Uint32> style_collection;
			
			enum Style
			{
				Regular = 0,
				Bold = 1 << 0,
				Italic = 1 << 1,
				Underlined = 1 << 2,
				StrikeThrough = 1 << 3
			};
			
			CustomText();
			
			CustomText(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30);
			
			CustomText(const sf::String& string, const sf::Font& font, unsigned int characterSize, const sf::Color& fillColor, style_collection style);
			
			void setString(const sf::String& string);
			
			void setFont(const sf::Font& font);
			
			void setCharacterSize(unsigned int size);
			
			void setLineSpacing(float spacingFactor);
			
			void setLetterSpacing(float spacingFactor);
			
			void setStyle(style_collection style);
			
			void addStyle(Uint32 style);
			
			void removeStyle(Uint32 style);
			
			void setFillColor(const Color& color);
			
			void setOutlineColor(const Color& color);
			
			void setOutlineThickness(float thickness);
			
			const sf::String& getString() const;
			
			const sf::Font* getFont() const;
			
			unsigned int getCharacterSize() const;
			
			float getLetterSpacing() const;
			
			float getLineSpacing() const;
			
			style_collection getStyle() const;
			
			const sf::Color& getFillColor() const;
			
			const sf::Color& getOutlineColor() const;
			
			float getOutlineThickness() const;
			
			Vector2f findCharacterPos(std::size_t index) const;
			
			sf::FloatRect getLocalBounds() const;
			
			sf::FloatRect getGlobalBounds() const;
			
			void setBackGroundColor(const sf::Color& color, float height);
			
			const sf::Color* getBackGroundColor() const;
			
			void clearBackGround();
		
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
			void ensureGeometryUpdate() const;
			
			//member data
			sf::String m_string;
			const Font* m_font;
			unsigned int m_characterSize;
			float m_letterSpacingFactor;
			float m_lineSpacingFactor;
			float backgroundHeight;
			style_collection m_style;
			sf::Color m_fillColor;
			const sf::Color* m_backGroundColor;
			sf::Color m_outlineColor;
			float m_outlineThickness;
			mutable sf::VertexArray m_vertices;
			mutable sf::VertexArray m_outlineVertices;
			mutable sf::FloatRect m_bounds;
			mutable bool m_geometryNeedUpdate;
			mutable Uint64 m_fontTextureId;
	};
}  //namespace sf

#endif //CUSTOM_TEXT_HPP
