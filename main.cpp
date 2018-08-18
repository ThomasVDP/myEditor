#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Utilities/StandardCursor.hpp"
#include "Utilities/RichText.hpp"
#include <iostream>

sf::String getLinesAsString(sf::String lines[]);
const int MAX_LINES = 99;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "TVDP's Text Editor");
	window.setFramerateLimit(60);
	
	sf::Font font;
	if (!font.loadFromFile("font/Verdana.ttf"))
		return EXIT_FAILURE;
	
	//change cursor to text cursor
	sf::StandardCursor Cursor(sf::StandardCursor::HAND);
	Cursor.set(window.getSystemHandle());
	
	sf::Text cursorText;
	cursorText.setFont(font);
	cursorText.setString("|");
	cursorText.setCharacterSize(14);
	cursorText.setFillColor(sf::Color::Black);
	
	sf::RichText richText;
	richText.setFont(font);
	richText.addStyle(sf::CustomText::Bold);
	richText.setCharacterSize(14);
	richText.setColor(sf::Color::Black);
	richText.setString("mmmmmmm");
	richText.addString("test2");
	richText.setString("aaa", 0, 2);
	richText.setCharacterSize(25, 4, 8);
	richText.setCharacterSize(20, 5, 6);
	richText.addStyle(sf::CustomText::Italic, 0, 2);
	std::cout << richText.getTextList().size() << std::endl;
	
	int cursorY = 0;
	int cursorX = 0;
	int preferredX = 0;
	int linesUsed = 1;
	bool shown = true;
	const int blinkFreq = 30;
	int blinkCnt = 0;
	
	sf::String lines[MAX_LINES];
	sf::Text text;
	text.setFont(font);
	text.setString(getLinesAsString(lines));
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::Black);
	
	while (window.isOpen())
	{
		sf::Event event;
		
		// toggle every blinkFreq cycles
		if(++blinkCnt >= blinkFreq)
        {
			if (shown)
			{
				shown = false;
				cursorText.setString("");
			} else {
				shown = true;
				cursorText.setString("|");
			}
			blinkCnt = 0;
		}
        
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::LostFocus)
				//save file
				continue;
			if (event.type == sf::Event::GainedFocus)
				//reload file
				continue;
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 13)
				{
					if (linesUsed < MAX_LINES)
					{
						//add lines
						linesUsed += 1;
						sf::String backupLine = lines[cursorY + 1];
						lines[cursorY + 1] = lines[cursorY].substring(cursorX, sf::String::InvalidPos);
						lines[cursorY] = lines[cursorY].substring(0, cursorX);
						int i = cursorY + 2;
						while (i < linesUsed)
						{
							sf::String backup = lines[i];
							lines[i] = backupLine;
							backupLine = backup;
							i += 1;
						}
						cursorY += 1;
						cursorX = 0;
						preferredX = cursorX;
					}
				} else if (event.text.unicode == 8)
				{
					if (cursorX == 0 && cursorY > 0)
					{
						linesUsed -= 1;
						sf::String backup = lines[cursorY - 1] + lines[cursorY].substring(cursorX, sf::String::InvalidPos);
						cursorX = lines[cursorY - 1].getSize();
						preferredX = cursorX;
						lines[cursorY - 1] = backup;
						for (int i = cursorY; i < linesUsed; i++)
						{
							lines[i] = lines[i + 1];
						}
						lines[linesUsed] = "";
						cursorY -= 1;
					} else if (cursorX > 0) {
						lines[cursorY] = lines[cursorY].substring(0, cursorX - 1) + lines[cursorY].substring(cursorX, sf::String::InvalidPos);
						cursorX -= 1;
						preferredX = cursorX;
					}
				} else if (event.text.unicode == 127)
				{
					if (((unsigned int)cursorX) == lines[cursorY].getSize() && linesUsed > 1)
					{
						linesUsed -= 1;
						lines[cursorY] += lines[cursorY + 1];
						for (int i = cursorY + 1; i < linesUsed; i++)
						{
							lines[i] = lines[i + 1];
						}
						lines[linesUsed] = "";
					} else if (cursorX >= 0 && ((unsigned int)cursorX) < lines[cursorY].getSize()) {
						lines[cursorY] = lines[cursorY].substring(0, cursorX) + lines[cursorY].substring(cursorX + 1, sf::String::InvalidPos);
					}
				} else {
					lines[cursorY].insert(cursorX, event.text.unicode);
					cursorX += 1;
					preferredX = cursorX;
				}
				text.setString(getLinesAsString(lines));
			}
			
			if (event.type == sf::Event::KeyReleased)
			{
				
			}
			
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					if (cursorX > 0) {
						cursorX -= 1;
						preferredX = cursorX;
					} else if (cursorY > 0) {
						cursorY -= 1;
						preferredX = cursorX;
						cursorX = lines[cursorY].getSize();
					}
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					if (((unsigned int)cursorX) < lines[cursorY].getSize())
					{
						cursorX += 1;
						preferredX = cursorX;
					} else if (cursorY + 1 < linesUsed) {
						cursorY += 1;
						cursorX = 0;
						preferredX = cursorX;
					}
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					if (cursorY > 0)
					{
						cursorY -= 1;
						if (((unsigned int)preferredX) > lines[cursorY].getSize())
						{
							cursorX = lines[cursorY].getSize();
						} else {
							cursorX = preferredX;
						}
					}
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					if (cursorY + 1 < linesUsed)
					{
						cursorY += 1;
						if (((unsigned int)preferredX) > lines[cursorY].getSize())
						{
							cursorX = lines[cursorY].getSize();
						} else {
							cursorX = preferredX;
						}
					}
				}
			}
		}
		cursorText.setPosition(sf::Text(lines[cursorY].substring(0, cursorX), font, 14).getGlobalBounds().width - 1, cursorY * 17);

		window.clear(sf::Color::White);
		window.draw(text);
		window.draw(richText);
		window.draw(cursorText);
		window.display();
	}

	return EXIT_SUCCESS;
}

sf::String getLinesAsString(sf::String lines[])
{
	sf::String result = "";
	for (int i = 0; i < MAX_LINES; i++)
	{
		result += lines[i] + "\n";
	}
	return result;
}
