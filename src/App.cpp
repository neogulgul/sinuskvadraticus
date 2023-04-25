#include "headers/App.hpp"

#define sinkColor sf::Color(255, 0, 0)
#define coskColor sf::Color(0, 0, 255)

float amplitude = 32;
float period = 360;

float sink(float v)
{
	using namespace std;

	v = fmod(v, 360);

	if (v == 180) { return 0; }

	if (v >= 45 && v <= 135)
	{
		return 1;
	}
	else if (v >= 135 && v <= 225)
	{
		v = degToRad(v);
		return -tan(v);
	}
	else if (v >= 225 && v <= 315)
	{
		return -1;
	}
	else
	{
		v = degToRad(v);
		return tan(v);
	}
}

float cosk(float v)
{
	using namespace std;

	v = fmod(v, 360);

	if (v == 90 || v == 270) { return 0; }

	if (v >= 45 && v <= 135)
	{
		v = degToRad(v);
		return 1 / tan(v);
	}
	else if (v >= 135 && v <= 225)
	{
		return -1;
	}
	else if (v >= 225 && v <= 315)
	{
		v = degToRad(v);
		return -1 / tan(v);
	}
	else
	{
		return 1;
	}
}

App::App(unsigned int targetFPS, sf::Vector2f viewSize, sf::Vector2u windowSize, std::string windowTitle)
: Root(targetFPS, viewSize, windowSize, windowTitle)
{
	dot.setRadius(1);
	dot.setOrigin({dot.getRadius(), dot.getRadius()});
	dot.setPointCount(10);

	functionLine.setSize({256, 2});
	functionLine.setOrigin(functionLine.getSize() / 2.f);

	vIndicator.setSize({2, amplitude * 2 + 2});
	vIndicator.setOrigin(vIndicator.getSize() / 2.f);
	vIndicator.setPosition(viewSize / 2.f);
	vIndicator.setFillColor(sf::Color::Transparent);
	vIndicator.setOutlineColor(sf::Color::White);
	vIndicator.setOutlineThickness(-0.5);
}

void App::handleWindowEvents()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseWheelMoved:
				handleMouseWheelMoved(event);
				break;

			case sf::Event::TextEntered:
				handleTextEntered(event);
				break;
		}
	}
}

void App::handleMouseWheelMoved(sf::Event event)
{
	switch (event.mouseWheel.delta)
	{
		case MouseWheel::Forward:
			break;

		case MouseWheel::Backward:
			break;
	}
}

void App::handleTextEntered(sf::Event event)
{
	char character = static_cast<char>(event.text.unicode);
	// ...
}

void App::update()
{
	handlePress(pressing(screenshotKey), screenshotPress);
	if (screenshotPress.pressedThisFrame) { takeScreenshot = true; }
	handlePress(pressing(pauseKey), pausePress);
	if (pausePress.pressedThisFrame) { toggle(paused); }

	if (paused)
	{
		handlePress(pressing(plusKey), plusPress);
		handlePress(pressing(minusKey), minusPress);

		if (plusPress.pressedThisFrame) { v++; }
		if (minusPress.pressedThisFrame) { v--; }
	}
	else
	{
		v += 1;
		if (v >= 360) { v = 0; }
	}
}

void App::draw()
{
	drawGraph();
	text.draw("FPS: " + std::to_string(averageFPS), Start, Start, {1, 1});

	std::stringstream ss;

	ss << "amplitude = " << amplitude;
	text.draw(ss.str(), Start, Start, {1, 1 + text.getLineSpacing() * 1});
	ss.str("");
	ss << "period = " << period;
	text.draw(ss.str(), Start, Start, {1, 1 + text.getLineSpacing() * 2});
	ss.str("");
	ss << "v = " << v;
	text.draw(ss.str(), Start, Start, {1, 1 + text.getLineSpacing() * 3});
	ss.str("");
	ss << "y, sink(v) = " << sink(period + v) * amplitude;
	text.draw(ss.str(), Start, Start, {1, 1 + text.getLineSpacing() * 4}, sinkColor);
	ss.str("");
	ss << "x, cosk(v) = " << cosk(period + v) * amplitude;
	text.draw(ss.str(), Start, Start, {1, 1 + text.getLineSpacing() * 5}, coskColor);
	ss.str("");

	text.draw("v", Center, End, {viewSize.x * 0.5f, viewSize.y * 0.5f - amplitude - text.getLineSpacing() / 2});

	ss << " " << amplitude;
	text.draw(ss.str(), Start, Center, {1, viewSize.y * 0.5f - amplitude});
	ss.str("");
	text.draw(" 0", Start, Center, {1, viewSize.y * 0.5f});
	ss << "-" << amplitude;
	text.draw(ss.str(), Start, Center, {1, viewSize.y * 0.5f + amplitude});
	ss.str("");

	if (paused)
	{
		text.draw("Paused" , End, Start, {viewSize.x - 1, 1 + text.getLineSpacing() * 0});
		text.draw("w: ++", End, Start, {viewSize.x - 1, 1 + text.getLineSpacing() * 1});
		text.draw("s: --", End, Start, {viewSize.x - 1, 1 + text.getLineSpacing() * 2});
	}
}

void App::drawGraph()
{
	drawFunctionLines();

	window.draw(vIndicator);

	drawFunctions(v);
}

void App::drawFunctionLines()
{
	// y = amplitude
	functionLine.setPosition(viewSize.x * 0.5, viewSize.y * 0.5f - amplitude);
	functionLine.setFillColor(sf::Color(127, 255, 127, 127));
	window.draw(functionLine);
	// y = 0
	functionLine.setPosition(viewSize.x * 0.5, viewSize.y * 0.5f);
	functionLine.setFillColor(sf::Color(127, 127, 255, 127));
	window.draw(functionLine);
	// y = -amplitude
	functionLine.setPosition(viewSize.x * 0.5, viewSize.y * 0.5f + amplitude);
	functionLine.setFillColor(sf::Color(255, 127, 127, 127));
	window.draw(functionLine);
}

void App::drawFunctions(float v)
{
	#define balls 1000

	for (int i = 0; i < balls; i++)
	{
		float x = (i + 0.5) / balls;

		// sink
		dot.setFillColor(sinkColor);
		dot.setPosition(viewSize.x * x, viewSize.y * 0.5f + sink(period * (x + 0.5) + v) * amplitude);
		window.draw(dot);

		// cosk
		dot.setFillColor(coskColor);
		dot.setPosition(viewSize.x * x, viewSize.y * 0.5f + cosk(period * (x + 0.5) + v) * amplitude);
		window.draw(dot);
	}

	dot.setFillColor(sf::Color::Yellow);
	// sink
	dot.setPosition(viewSize.x * 0.5f, viewSize.y * 0.5f + sink(period + v) * amplitude);
	window.draw(dot);
	// cosk
	dot.setPosition(viewSize.x * 0.5f, viewSize.y * 0.5f + cosk(period + v) * amplitude);
	window.draw(dot);
}
