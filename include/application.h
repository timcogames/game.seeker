#pragma once

#include <sway/ois.h>

using namespace sway;

class Application : public ois::KeyboardListener, public ois::MouseListener {
public:
	Application();
	~Application();

	virtual void onKeyPressed(const ois::KeyboardEventArgs & event) override;

	virtual void onKeyReleased(const ois::KeyboardEventArgs & event) override;

	virtual void onMouseButtonDown(const ois::MouseEventArgs & event) override;

	virtual void onMouseButtonUp(const ois::MouseEventArgs & event) override;

	virtual void onMouseMove(const ois::MouseEventArgs & event) override;
};
