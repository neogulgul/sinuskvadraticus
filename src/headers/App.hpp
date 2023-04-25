#pragma once

#include <SFML/Graphics.hpp>

#include "Root.hpp"

#define screenshotKey keyboard::F1
#define pauseKey keyboard::Space
#define plusKey keyboard::W
#define minusKey keyboard::S

struct App : Root
{
	Press screenshotPress;

	Press pausePress;
	bool paused = false;

	Press plusPress;
	Press minusPress;

	float v = 0;

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
