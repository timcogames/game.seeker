#include <application.h>
#include <sway/ois/keycodes.h>

#include <stdio.h>

Application::Application() {
	// Empty
}

Application::~Application() {
	// Empty
}

void Application::onKeyPressed(const ois::KeyboardEventArgs & event) {
	printf("key pressed: %i\n", event.keycode);
}

void Application::onKeyReleased(const ois::KeyboardEventArgs & event) {
	printf("key released: %i\n", event.keycode);
}

void Application::onMouseButtonDown(const ois::MouseEventArgs & event) {
	if (event.button == 1)
		printf("Left mouse down\n");
	else if (event.button == 2)
		printf("Middle mouse down\n");
	else if (event.button == 3)
		printf("Right mouse down\n");
	else if (event.button == 4)
		printf("Mouse scroll up\n");
	else if (event.button == 5)
		printf("Mouse scroll down\n");
}

void Application::onMouseButtonUp(const ois::MouseEventArgs & event) {
	if (event.button == 1)
		printf("Left mouse up\n");
	else if (event.button == 2)
		printf("Middle mouse up\n");
	else if (event.button == 3)
		printf("Right mouse up\n");
}

void Application::onMouseMove(const ois::MouseEventArgs & event) {
	printf("Mouse X: %i, Y: %i\n", event.x, event.y);
}
