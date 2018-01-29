#include <sway/glx11/canvas.h>
#include <sway/core.h>
#include <sway/math.h>

using namespace sway;

int main(int argc, char * argv[]) {
	glx11::WindowInitialParams params;
	params.title = "seeker";
	params.sizes[glx11::kWindowSize] = math::TSize<s32_t>(800, 600);
	params.sizes[glx11::kWindowSize_Min] = math::TSize<s32_t>(640, 480);
	params.sizes[glx11::kWindowSize_Max] = math::TSize<s32_t>(1024, 768);
	params.fullscreen = false;
	params.resizable = true;

	glx11::Canvas * canvas = glx11::createSurface(params);
	canvas->show();

	while (canvas->eventLoop(true)) {
		canvas->getContext()->makeCurrent();

		canvas->getContext()->present();
		canvas->getContext()->doneCurrent();
	}

	delete canvas;
	return 0;
}
