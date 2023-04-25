#include <SFML/Graphics.hpp>

#include "headers/helper.hpp"

float degToRad(float deg)
{
	return deg * (PI / 180);
}

float radToDeg(float rad)
{
	return rad * (180 / PI);
}

void toggle(bool &boolean)
{
	if (boolean)
	{
		boolean = false;
	}
	else
	{
		boolean = true;
	}
}

bool pressing(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool pressing(sf::Mouse::Button button)
{
	return sf::Mouse::isButtonPressed(button);
}

void handlePress(bool pressing, Press &press)
{
	press.pressedThisFrame = false;

	if (pressing)
	{
		if (!press.pressedLastFrame)
		{
			press.pressedLastFrame = true;
			press.pressedThisFrame = true;
		}
	}
	else
	{
		press.pressedLastFrame = false;
	}
}

std::string boolToString(bool boolean)
{
	if (boolean) { return "True"; }
	return "False";
}

std::string removeFromString(std::string string, int start, int range)
{
	std::string returnString;

	if (start < 0 || range < 0 || start + range > string.size()) { return "Error!"; } // invalid start and/or range

	for (int i = 0; i < string.size(); i++)
	{
		if (i >= start && i < start + range) { continue; }

		returnString += string[i];
	}

	return returnString;
}

std::string replaceStringSubstring(std::string string, std::string substring, std::string replacement)
{
	string.replace(string.find(substring), substring.size(), replacement);
	return string;
}

sf::Vector2f relativeViewPosition(sf::View* view, sf::Vector2f position)
{
	return {view->getCenter().x - view->getSize().x / 2 + position.x, view->getCenter().y - view->getSize().y / 2 + position.y};
}

sf::Vector2f align(sf::Vector2f size, Alignment horizontalAlignment, Alignment verticalAlignment, sf::Vector2f position)
{
	switch (horizontalAlignment)
	{
		case Start:
			position.x -= 0;
			break;

		case Center:
			position.x -= size.x / 2;
			break;

		case End:
			position.x -= size.x;
			break;
	}

	switch (verticalAlignment)
	{
		case Start:
			position.y -= 0;
			break;

		case Center:
			position.y -= size.y / 2;
			break;

		case End:
			position.y -= size.y;
			break;
	}

	return position;
}

void createFile(std::string path)
{
	if (fs::is_directory(path))
	{
		fs::remove_all(path);
	}
	if (!fs::is_regular_file(path))
	{
		std::ofstream file(path);
		file.close();
	}
}

void createFolder(std::string path)
{
	if (fs::is_regular_file(path))
	{
		fs::remove(path);
	}
	if (!fs::is_directory(path))
	{
		fs::create_directory(path);
	}
}

void writeToFile(std::string path, std::string text)
{
	if (!fs::is_regular_file(path)) { createFile(path); }
	std::ofstream file(path);
	file << text;
	file.close();
}

std::string readFromFile(std::string path)
{
	std::stringstream ss;

	if (fs::is_regular_file(path))
	{
		std::ifstream file(path);
		while (file >> ss.rdbuf());
		file.close();
	}

	return ss.str();
}

sf::Vector2i center(sf::Vector2i size) { return sf::Vector2i(size.x / 2, size.y / 2); }
sf::Vector2u center(sf::Vector2u size) { return sf::Vector2u(size.x / 2, size.y / 2); }
sf::Vector2f center(sf::Vector2f size) { return sf::Vector2f(size.x / 2, size.y / 2); }

sf::Vector2i vector2Int(sf::Vector2u vector2) { return sf::Vector2i(vector2.x, vector2.y); }
sf::Vector2i vector2Int(sf::Vector2f vector2) { return sf::Vector2i(vector2.x, vector2.y); }

sf::Vector2u vector2UInt(sf::Vector2i vector2) { return sf::Vector2u(vector2.x, vector2.y); }
sf::Vector2u vector2UInt(sf::Vector2f vector2) { return sf::Vector2u(vector2.x, vector2.y); }

sf::Vector2f vector2Float(sf::Vector2i vector2) { return sf::Vector2f(vector2.x, vector2.y); }
sf::Vector2f vector2Float(sf::Vector2u vector2) { return sf::Vector2f(vector2.x, vector2.y); }

float getTop   (sf::FloatRect rect) { return rect.top; }
float getBottom(sf::FloatRect rect) { return rect.top + rect.height; }
float getLeft  (sf::FloatRect rect) { return rect.left; }
float getRight (sf::FloatRect rect) { return rect.left + rect.width; }

void decrease(float &value, float decreasement)
{
	if (value > 0)
	{
		value -= decreasement;
		if (value < 0) { value = 0; }
	}
	else if (value < 0)
	{
		value += decreasement;
		if (value > 0) { value = 0; }
	}
}
