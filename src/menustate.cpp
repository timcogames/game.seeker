#include <menustate.h>
#include <playstate.h>
#include <sway/ois/keycodes.h>
#include <sway/game/framework.h>

#include <stdio.h>

MenuState MenuState::_instance;

void MenuState::enter() {
	printf("MenuState::enter\n");

	auto context = static_cast<game::Framework *>(getContext());
	auto keyboard = context->getInput()->getDevice<ois::Keyboard>();
	// auto mouse = context->getInput()->getDevice<ois::Mouse>();

	keyboard->setListener(this);
	context->getCanvas()->addEventBinding(KeyPress, boost::bind(&ois::Keyboard::notifyKeyPressed, keyboard, _1));
	context->getCanvas()->addEventBinding(KeyRelease, boost::bind(&ois::Keyboard::notifyKeyReleased, keyboard, _1));

	// mouse->setListener(this);
	// context->getCanvas()->addEventBinding(MotionNotify, boost::bind(&ois::Mouse::notifyMouseMove, mouse, _1));
	// context->getCanvas()->addEventBinding(ButtonPress, boost::bind(&ois::Mouse::notifyMouseButtonDown, mouse, _1));
	// context->getCanvas()->addEventBinding(ButtonRelease, boost::bind(&ois::Mouse::notifyMouseButtonUp, mouse, _1));

	_changeState = false;
}

void MenuState::exit() {
	printf("MenuState::exit\n");
}

void MenuState::pause() {
	// Empty
}

void MenuState::resume() {
	// Empty
}

void MenuState::frameStarted(float timeStep) {
	if (_changeState)
		static_cast<game::Framework *>(getContext())->startup(PlayState::getInstance());
}

void MenuState::frameEnded() {
	// Empty
}

void MenuState::onKeyPressed(const ois::KeyboardEventArgs & event) {
	if (event.keycode == ois::KeyCodes::kKeyCode_W) {
		_changeState = true;
	}
}

void MenuState::onKeyReleased(const ois::KeyboardEventArgs & event) {
	// Empty
}

void MenuState::onMouseButtonDown(const ois::MouseEventArgs & event) {
	// Empty
}

void MenuState::onMouseButtonUp(const ois::MouseEventArgs & event) {
	// Empty
}

void MenuState::onMouseMove(const ois::MouseEventArgs & event) {
	// Empty
}
