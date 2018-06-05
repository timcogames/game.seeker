#include <application.h>
#include <sway/ois/keycodes.h>

#include <stdio.h>

Application::Application()
	: _quit(true) {

	// Empty
}

Application::~Application() {
	// Empty
}

void Application::onKeyPressed(const ois::KeyboardEventArgs & event) {
	if (event.keycode == ois::KeyCodes::kKeyCode_Q)
		_quit = false;
}

void Application::onKeyReleased(const ois::KeyboardEventArgs & event) {
	// Empty
}

void Application::onMouseButtonDown(const ois::MouseEventArgs & event) {
	// Empty
}

void Application::onMouseButtonUp(const ois::MouseEventArgs & event) {
	// Empty
}

void Application::onMouseMove(const ois::MouseEventArgs & event) {
	// Empty
}

bool Application::isQuit() const {
	return _quit;
}
