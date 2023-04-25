#include "headers/App.hpp"

#define targetFPS    60
#define viewWidth    256
#define viewHeight   256
#define windowWidth  512
#define windowHeight 512
#define windowTitle  "hello, world"

int main()
{
	App app(targetFPS, {viewWidth, viewHeight}, {windowWidth, windowHeight}, windowTitle);

	app.run();

	return 0;
}
