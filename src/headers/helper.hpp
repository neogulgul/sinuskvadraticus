#pragma once

#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <random>

namespace fs = std::filesystem;

#define int_dist std::uniform_int_distribution<int>

const float PI = std::numbers::pi;

using keyboard = sf::Keyboard;
using    mouse = sf::Mouse;

struct Press
{
	bool pressedThisFrame = false;
	bool pressedLastFrame = false;
};

enum Alignment { Start, Center, End };

float degToRad(float deg);

float radToDeg(float rad);

void toggle(bool &boolean);

bool pressing(sf::Keyboard::Key key);

bool pressing(sf::Mouse::Button button);

void handlePress(bool pressing, Press &press);

std::string boolToString(bool boolean);

std::string removeFromString(std::string string, int start, int range);

std::string replaceStringSubstring(std::string string, std::string substring, std::string replacement = "");

sf::Vector2f relativeViewPosition(sf::View* view, sf::Vector2f position);

sf::Vector2f align(sf::Vector2f size, Alignment horizontalAlignment, Alignment verticalAlignment, sf::Vector2f position);

void createFile(std::string path);

void createFolder(std::string path);

void writeToFile(std::string path, std::string text);

std::string readFromFile(std::string path);

sf::Vector2i center(sf::Vector2i size);
sf::Vector2u center(sf::Vector2u size);
sf::Vector2f center(sf::Vector2f size);

sf::Vector2i vector2Int(sf::Vector2u vector2);
sf::Vector2i vector2Int(sf::Vector2f vector2);

sf::Vector2u vector2UInt(sf::Vector2i vector2);
sf::Vector2u vector2UInt(sf::Vector2f vector2);

sf::Vector2f vector2Float(sf::Vector2i vector2);
sf::Vector2f vector2Float(sf::Vector2u vector2);

float getTop   (sf::FloatRect rect);
float getBottom(sf::FloatRect rect);
float getLeft  (sf::FloatRect rect);
float getRight (sf::FloatRect rect);

void decrease(float &value, float decreasement);
