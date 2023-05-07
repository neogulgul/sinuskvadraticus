#include "headers/App.hpp"

#define sinkColor sf::Color(255, 0, 0)
#define coskColor sf::Color(0, 0, 255)

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

float tank(float v)
{
	if (v == 90 || v == 270) { return NAN; }
	return sink(v) / cosk(v);
}

App::App(unsigned int targetFPS, sf::Vector2f viewSize, sf::Vector2u windowSize, std::string windowTitle)
: Root(targetFPS, viewSize, windowSize, windowTitle)
{
	dot.setRadius(1);
	dot.setOrigin({dot.getRadius(), dot.getRadius()});
	dot.setPointCount(10);

	functionLine.setSize({256, 2});
	functionLine.setOrigin(functionLine.getSize() / 2.f);

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
	handlePress(pressing(amplitudeCalcKey), amplitudeCalcPress);
	if (amplitudeCalcPress.pressedThisFrame) { toggle(amplitudeCalc); }
	handlePress(pressing(hideStuffKey), hideStuffPress);
	if (hideStuffPress.pressedThisFrame) { toggle(hideStuff); }

	handlePress(pressing(amplitudePlusKey), amplitudePlusPress);
	handlePress(pressing(amplitudeMinusKey), amplitudeMinusPress);
	if (amplitudePlusPress.pressedThisFrame) { amplitude++; }
	if (amplitudeMinusPress.pressedThisFrame) { amplitude--; }

	handlePress(pressing(periodPlusKey), periodPlusPress);
	handlePress(pressing(periodMinusKey), periodMinusPress);
	if (periodPlusPress.pressedThisFrame) { period += periodIncrement; }
	if (periodMinusPress.pressedThisFrame) { period -= periodIncrement; }

	if (paused)
	{
		handlePress(pressing(vPlusKey), vPlusPress);
		handlePress(pressing(vMinusKey), vMinusPress);
		if (vPlusPress.pressedThisFrame) { v++; }
		if (vMinusPress.pressedThisFrame) { v--; }
	}
	else
	{
		v += 1;
	}

	if (v >= 360) { v = 0; }
}

void App::draw()
{
	drawGraph();
	text.draw("FPS: " + std::to_string(averageFPS), Start, Start, {1, 1});

	if (hideStuff) { return; }

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
	amplitudeCalc ? ss << "y, sink(v) = " << sink(period + v) * amplitude
	              : ss << "y, sink(v) = " << sink(period + v);
	text.draw(ss.str(), Start, Start, {1, 1 + text.getLineSpacing() * 4}, sinkColor);
	ss.str("");
	amplitudeCalc ? ss << "x, cosk(v) = " << cosk(period + v) * amplitude
	              : ss << "x, cosk(v) = " << cosk(period + v);
	text.draw(ss.str(), Start, Start, {1, 1 + text.getLineSpacing() * 5}, coskColor);
	ss.str("");

	text.draw("v", Center, End, {viewSize.x * 0.5f, viewSize.y * 0.5f - amplitude - text.getLineSpacing() / 2});

	amplitudeCalc ? ss << " " << amplitude : ss << " " << 1;
	text.draw(ss.str(), Start, Center, {1, viewSize.y * 0.5f - amplitude});
	ss.str("");
	text.draw(" 0", Start, Center, {1, viewSize.y * 0.5f});
	amplitudeCalc ? ss << "-" << amplitude : ss << "-" << 1;
	text.draw(ss.str(), Start, Center, {1, viewSize.y * 0.5f + amplitude});
	ss.str("");

	if (paused)
	{
		text.draw("Paused" , End, Start, {viewSize.x - 1, 1 + text.getLineSpacing() * 0});
		text.draw("X: ++", End, Start, {viewSize.x - 1, 1 + text.getLineSpacing() * 1});
		text.draw("Z: --", End, Start, {viewSize.x - 1, 1 + text.getLineSpacing() * 2});
	}

	// Trigonometriska ettan
	// sin² v + cos² v = 1
	// (STÄMMER EJ)
	// ss << "sink^2 v + cosk^2 v = " << std::pow(sink(v), 2) + std::pow(cosk(v), 2);

	// Formler för dubbla vinkeln
	// sin 2v = 2 * sin v * cos v
	// (STÄMMER EJ)
	// ss << "sink 2v = " << sink(2 * v)
	//    << "\n"
	//    << "2 * sink v * cosk v = " << 2 * sink(v) * cosk(v);

	// cos 2v = cos² v - sin² v
	// (STÄMMER EJ)
	// ss << "cosk 2v = " << cosk(2 * v)
	//    << "\n"
	//    << "cosk^2 v - sin^2 v = " << std::pow(cosk(v), 2) - std::pow(sink(v), 2);

	// cos 2v = 2 * cos² v - 1
	// (STÄMMER EJ)
	// ss << "cosk 2v = " << cosk(2 * v)
	//    << "\n"
	//    << "2 * cosk^2 v - 1 = " << 2 * std::pow(cosk(v), 2) - 1;

	// cos 2v = 1 - 2 * sin² v
	// (STÄMMER EJ)
	// ss << "cosk 2v = " << cosk(2 * v)
	//    << "\n"
	//    << "1 - 2 * sink^2 v = " << 1 - 2 * std::pow(sink(v), 2);

	// tan 2v = (2 * tan v) / (1 - tan² v)
	// (STÄMMER FAKTISKT)
	// ss << "tank 2v = " << tank(2 * v)
	//    << "\n"
	//    << "(2 * tank v) / (1 - tank^2 v) = " << (2 * tank(v)) / (1 - std::pow(tank(v), 2));

	// text.draw(ss.str(), Center, Center, {viewSize.x * 0.5f, viewSize.y * 0.75f});
	// ss.str("");
}

void App::drawGraph()
{
	drawFunctionLines();

	if (!hideStuff)
	{
		vIndicator.setSize({2, amplitude * 2 + 2});
		vIndicator.setOrigin(vIndicator.getSize() / 2.f);
		window.draw(vIndicator);
	}

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
	#define balls 2000

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

	if (!hideStuff)
	{
		dot.setFillColor(sf::Color::Yellow);
		// sink
		dot.setPosition(viewSize.x * 0.5f, viewSize.y * 0.5f + sink(period + v) * amplitude);
		window.draw(dot);
		// cosk
		dot.setPosition(viewSize.x * 0.5f, viewSize.y * 0.5f + cosk(period + v) * amplitude);
		window.draw(dot);
	}
}
