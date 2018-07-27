#include <sway/glx11/xscreenconnection.h>
#include <sway/glx11/canvas.h>
#include <sway/ois.h>
#include <sway/core.h>
#include <sway/math.h>
#include <sway/gapi.h>
#include <sway/graphics.h>

#include <framework.h>
#include <application.h>

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared

using namespace sway;

int main(int argc, char * argv[]) {
	glx11::WindowInitialParams params;
	params.title = "seeker";
	params.sizes[core::detail::toUnderlying(glx11::WindowSize_t::kOrigin)] = math::size2i_t(800, 600);
	params.sizes[core::detail::toUnderlying(glx11::WindowSize_t::kMin)] = math::size2i_t(640, 480);
	params.sizes[core::detail::toUnderlying(glx11::WindowSize_t::kMax)] = math::size2i_t(1024, 768);
	params.fullscreen = false;
	params.resizable = true;

	auto connection = boost::make_shared<glx11::XScreenConnection>();
	auto canvas = boost::make_shared<glx11::Canvas>(connection, params);

	canvas->show();
	canvas->getContext()->makeCurrent();

	gapi::Extensions::define();

	ois::InputManager * inputManager = new ois::InputManager(connection->getDisplay(), canvas->getWindowHandle());
	ois::Keyboard * keyboard = static_cast<ois::Keyboard *>(inputManager->createDevice(ois::kDeviceType_Keyboard));
	ois::Mouse * mouse = static_cast<ois::Mouse *>(inputManager->createDevice(ois::kDeviceType_Mouse));
	
	canvas->addEventBinding(KeyPress, boost::bind(&ois::Keyboard::notifyKeyPressed, keyboard, _1));
	canvas->addEventBinding(KeyRelease, boost::bind(&ois::Keyboard::notifyKeyReleased, keyboard, _1));
	canvas->addEventBinding(MotionNotify, boost::bind(&ois::Mouse::notifyMouseMove, mouse, _1));
	canvas->addEventBinding(ButtonPress, boost::bind(&ois::Mouse::notifyMouseButtonDown, mouse, _1));
	canvas->addEventBinding(ButtonRelease, boost::bind(&ois::Mouse::notifyMouseButtonUp, mouse, _1));

	auto framework = boost::make_shared<Framework>(); 
	auto app = boost::make_shared<Application>();
	
	keyboard->setListener(app.get());
	mouse->setListener(app.get());

	while (canvas->eventLoop(app->isQuit())) {
		canvas->getContext()->makeCurrent();

		canvas->getContext()->present();
		canvas->getContext()->doneCurrent();
	}

	return 0;
}
