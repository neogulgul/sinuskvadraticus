#pragma once

#include <SFML/Graphics.hpp>

#include "Root.hpp"

// key bindings
#define screenshotKey     keyboard::F1
#define pauseKey          keyboard::Space
#define vPlusKey          keyboard::X
#define vMinusKey         keyboard::Z
#define amplitudePlusKey  keyboard::W
#define amplitudeMinusKey keyboard::S
#define amplitudeCalcKey  keyboard::E
#define periodPlusKey     keyboard::D
#define periodMinusKey    keyboard::A
#define hideStuffKey      keyboard::F

struct App : Root
{
	Press screenshotPress;

	Press pausePress;
	bool paused = false;

	Press vPlusPress;
	Press vMinusPress;

	Press amplitudePlusPress;
	Press amplitudeMinusPress;
	Press amplitudeCalcPress;
	bool amplitudeCalc = false;

	Press periodPlusPress;
	Press periodMinusPress;

	Press hideStuffPress;
	bool hideStuff = false;

	float v = 0;
	float amplitude = 32;
	float period = 360;
	float periodIncrement = 45;

	sf::CircleShape dot;
	sf::RectangleShape functionLine;
	sf::RectangleShape vIndicator;

	App(unsigned int targetFPS, sf::Vector2f viewSize, sf::Vector2u windowSize, std::string windowTitle);

	virtual void handleWindowEvents();

	void handleMouseWheelMoved(sf::Event event);

	void handleTextEntered(sf::Event event);

	virtual void update();

	virtual void draw();

	void drawGraph();
	void drawFunctionLines();
	void drawFunctions(float v);
};
