#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <sway/ois.h>
#include <sway/gapi.h>
#include <sway/graphics.h>
#include <sway/game.h>

using namespace sway;

class PlayState : public game::fsm::IStateBase, public ois::InputListener {
public:
	static PlayState _instance;
	static PlayState * getInstance() {
		return &_instance;
	}

	/*!
	 * \brief
	 *   Конструктор класса.
	 */
	PlayState() = default;

	/*!
	 * \brief
	 *   Деструктор класса.
	 */
	virtual ~PlayState() = default;

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
	boost::shared_ptr<graphics::Material> _material;
};

#endif // PLAYSTATE_H
