#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <sway/core.h>
#include <sway/graphics.h>

using namespace sway;

class Framework : public core::foundation::Context {
public:
	/*!
	 * \brief
	 *   Конструктор класса.
	 *
	 *   Выполняет инициализацию нового экземпляра класса.
	 */
	Framework();

	/*!
	 * \brief
	 *   Деструктор класса.
	 *
	 *   Освобождает захваченные ресурсы.
	 */
	~Framework();

private:
	graphics::RenderSubsystem * _renderSubsystem;
};

#endif // FRAMEWORK_H
