#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <sway/ois.h>
#include <sway/gapi.h>
#include <sway/graphics.h>
#include <sway/game.h>

using namespace sway;

class MenuState : public game::fsm::IStateBase, public ois::InputListener {
public:
	static MenuState _instance;
	static MenuState * getInstance() {
		return &_instance;
	}

	/*!
	 * \brief
	 *   Конструктор класса.
	 */
	MenuState() = default;

	/*!
	 * \brief
	 *   Деструктор класса.
	 */
	virtual ~MenuState() = default;

	virtual void enter() override;

	virtual void exit() override;

	virtual void pause() override;

	virtual void resume() override;

	virtual void frameStarted(float timeStep) override;

	virtual void frameEnded() override;

	#pragma region Реализация методов ois::InputListener

	virtual void onKeyPressed(const ois::KeyboardEventArgs & event) override;

	virtual void onKeyReleased(const ois::KeyboardEventArgs & event) override;

	virtual void onMouseButtonDown(const ois::MouseEventArgs & event) override;

	virtual void onMouseButtonUp(const ois::MouseEventArgs & event) override;

	virtual void onMouseMove(const ois::MouseEventArgs & event) override;

	#pragma endregion

private:
	bool _changeState;
};

#endif // MENUSTATE_H
