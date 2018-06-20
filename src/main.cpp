#include <sway/glx11/xscreenconnection.h>
#include <sway/glx11/canvas.h>
#include <sway/ois.h>
#include <sway/core.h>
#include <sway/math.h>
#include <sway/gapi.h>
#include <sway/graphics.h>

#include <application.h>

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared

using namespace sway;

int main(int argc, char * argv[]) {
	glx11::WindowInitialParams params;
	params.title = "seeker";
	params.sizes[glx11::kWindowSize] = math::TSize<s32_t>(800, 600);
	params.sizes[glx11::kWindowSize_Min] = math::TSize<s32_t>(640, 480);
	params.sizes[glx11::kWindowSize_Max] = math::TSize<s32_t>(1024, 768);
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

	graphics::RenderSubsystem * render = new graphics::RenderSubsystem();

	Application * app = new Application();
	keyboard->setListener(app);
	mouse->setListener(app);

	while (canvas->eventLoop(app->isQuit())) {
		canvas->getContext()->makeCurrent();

		canvas->getContext()->present();
		canvas->getContext()->doneCurrent();
	}

	delete app;
	return 0;
}
