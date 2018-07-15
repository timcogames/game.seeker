#include <framework.h>

Framework::Framework() {
	_renderSubsystem = new graphics::RenderSubsystem(this);
}

Framework::~Framework() {
	// Empty
}
