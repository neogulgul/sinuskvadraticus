#pragma once

#include "helper.hpp"
#include "Text.hpp"

struct Root
{
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;

	sf::Vector2f viewSize;
	sf::FloatRect viewport;

	bool takeScreenshot = false;

	unsigned int targetFPS, FPS, averageFPS;
	std::vector<unsigned int> pastFPS;
	unsigned int pastFPSMaxCount = 100;
	float     updateFPSDelta = 0.1; // the time between FPS counter update, in seconds
	sf::Clock updateFPSClock;       // used to only update the FPS counter after a certain amount of time has passed, to make it more readable
	sf::Clock   calcFPSClock;       // used to calculate FPS
	sf::Clock   displayClock;       // the time it takes the window to display everything drawn which is then subtracted when calculating FPS

	sf::Vector2f mousePosition;

	enum MouseWheel { Forward = 1, Backward = -1 };

	sf::VertexArray pixel;

	std::mt19937 rng;
	int_dist coinFlip;

	Text text;

	Root(unsigned int targetFPS, sf::Vector2f viewSize, sf::Vector2u windowSize, std::string windowTitle)
	{
		this->targetFPS = targetFPS;
		this->viewSize = viewSize;

		window.create({windowSize.x, windowSize.y}, windowTitle, sf::Style::Default);
		window.setFramerateLimit(targetFPS);
		view.setCenter(center(viewSize));
		view.setSize(viewSize);

		pixel.setPrimitiveType(sf::Quads);
		pixel.resize(4);

		rng.seed(std::random_device{}());
		coinFlip = int_dist(0, 1);

		text.init(&window);
	}

	void run()
	{
		while (window.isOpen())
		{
			handleWindowEvents();

			window.clear();

			calcFPS();

			updateMousePosition();

			update();

			updateViewport();

			window.setView(view);

			draw();

			displayClock.restart();

			window.display();

			if (takeScreenshot) { screenshot(); }
		}
	}

	void screenshot()
	{
		sf::Texture screenshotTexture;
		screenshotTexture.create(window.getSize().x, window.getSize().y);
		screenshotTexture.update(window);
		if (!fs::is_directory("screenshots"))
		{
			createFolder("screenshots");
		}

		std::chrono::time_point currentTime = std::chrono::system_clock::now();

		// removing "ns" from end of currentTime
		std::stringstream ss;
		ss << currentTime.time_since_epoch();
		ss.str(replaceStringSubstring(ss.str(), "ns"));

		screenshotTexture.copyToImage().saveToFile("screenshots/" + ss.str() + ".png");
		takeScreenshot = false;
	}

	void updateMousePosition()
	{
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}

	void updateViewport()
	{
		viewport = sf::FloatRect(view.getCenter() - center(viewSize), viewSize);
	}

	void calcFPS()
	{
		if (updateFPSClock.getElapsedTime().asSeconds() >= updateFPSDelta)
		{
			updateFPSClock.restart();
			FPS = std::floor(1.f / (calcFPSClock.getElapsedTime().asSeconds() - displayClock.getElapsedTime().asSeconds()));

			// average FPS
			pastFPS.push_back(FPS);
			if (pastFPS.size() > pastFPSMaxCount)
			{
				pastFPS.erase(pastFPS.begin());
			}
			averageFPS = 0;
			for (int i = 0; i < pastFPS.size(); i++)
			{
				averageFPS += pastFPS[i];
			}
			averageFPS /= pastFPS.size();
		}
		calcFPSClock.restart();
	}

	void drawPixel(sf::Vector2f position, sf::Color color = sf::Color::White) // this function is terribly inefficient on a large scale, but it works
	{
		pixel[0].position = { position.x    , position.y + 1 };
		pixel[1].position = { position.x    , position.y     };
		pixel[2].position = { position.x + 1, position.y     };
		pixel[3].position = { position.x + 1, position.y + 1 };
		for (int i = 0; i < 4; i++) { pixel[i].color = color; }
		window.draw(pixel);
	}

	virtual void handleWindowEvents() {}

	virtual void update() {}

	virtual void draw() {}
};
