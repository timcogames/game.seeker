#include <application.h>
#include <sway/ois/keycodes.h>

#include <stdio.h>

Application::Application()
	: _quit(true) {
	graphics::MaterialInitialInfo materialInitialInfo;
	materialInitialInfo.vsoInfo.type = gapi::kShaderType_Vertex;
	materialInitialInfo.vsoInfo.source = 
		"void main(void) {" \
		"gl_Position = vec4(0.0, 0.0, 0.0, 1.0);" \
		"}";
	materialInitialInfo.fsoInfo.type = gapi::kShaderType_Fragment;
	materialInitialInfo.fsoInfo.source = 
		"void main() {" \
		"gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);" \
		"}";
	_material = new graphics::Material(materialInitialInfo);
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
