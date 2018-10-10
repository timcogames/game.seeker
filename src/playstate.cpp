#include <playstate.h>
#include <menustate.h>
#include <sway/ois/keycodes.h>
#include <sway/game/framework.h>

#include <stdio.h>

PlayState PlayState::_instance;

void PlayState::enter() {
	printf("PlayState::enter\n");

	auto context = static_cast<game::Framework *>(getContext());
	auto keyboard = context->getInput()->getDevice<ois::Keyboard>();

	keyboard->setListener(this);

	context->getCanvas()->addEventBinding(KeyPress, boost::bind(&ois::Keyboard::notifyKeyPressed, keyboard, _1));
	context->getCanvas()->addEventBinding(KeyRelease, boost::bind(&ois::Keyboard::notifyKeyReleased, keyboard, _1));

	graphics::MaterialInitialInfo materialInitialInfo;
	materialInitialInfo.vsoInfo.type = gapi::ShaderType_t::kVertex;
	materialInitialInfo.vsoInfo.code = 
		"void main(void) {" \
			"gl_Position = vec4(0.0, 0.0, 0.0, 1.0);" \
		"}";
	materialInitialInfo.fsoInfo.type = gapi::ShaderType_t::kFragment;
	materialInitialInfo.fsoInfo.code = 
		"void main() {" \
			"gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);" \
		"}";
	_material = boost::make_shared<graphics::Material>(materialInitialInfo);
}

void PlayState::exit() {
	printf("PlayState::exit\n");
}

void PlayState::pause() {
	// Empty
}

void PlayState::resume() {
	// Empty
}

void PlayState::frameStarted(float timeStep) {
	// Empty
}

void PlayState::frameEnded() {
	// Empty
}

void PlayState::onKeyPressed(const ois::KeyboardEventArgs & event) {
	if (event.keycode == ois::KeyCodes::kKeyCode_S) {
		static_cast<game::Framework *>(getContext())->startup(MenuState::getInstance());
	}

	if (event.keycode == ois::KeyCodes::kKeyCode_Q) {
		static_cast<game::Framework *>(getContext())->terminate();
	}
}

void PlayState::onKeyReleased(const ois::KeyboardEventArgs & event) {
	// Empty
}

void PlayState::onMouseButtonDown(const ois::MouseEventArgs & event) {
	// Empty
}

void PlayState::onMouseButtonUp(const ois::MouseEventArgs & event) {
	// Empty
}

void PlayState::onMouseMove(const ois::MouseEventArgs & event) {
	// Empty
}
