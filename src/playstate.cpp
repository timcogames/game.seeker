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

	auto renderQueue = getSubsystem<graphics::RenderSubsystem>()->getQueueByIdx(0);
	auto renderSubqueue = renderQueue->getSubqueues(graphics::RenderSubqueueGroup_t::kOpaque)[0];

	gapi::ShaderCreateInfoSet shaderCreateInfoSet;
	shaderCreateInfoSet.vs.type = gapi::ShaderType_t::kVertex;
	shaderCreateInfoSet.vs.code = 
		"attribute vec3 attr_position;" \
		"void main() {" \
		"	gl_Position = vec4(attr_position, 1.0);" \
	 	"}";
	shaderCreateInfoSet.fs.type = gapi::ShaderType_t::kFragment;
	shaderCreateInfoSet.fs.code = 
		"void main() {" \
		"	gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);" \
		"}";
	_material = std::make_shared<graphics::Material>(shaderCreateInfoSet);

	auto data = std::make_shared<graphics::VertexData>(3);
	auto channel = data->createChannel<math::vec3f_t>(gapi::VertexSemantic_t::kPosition);
	
	auto d0 = math::vec3f_t(-0.5f,-0.5f, 0.0f);
	channel->addAnyData(d0.data());
	auto d1 = math::vec3f_t( 0.5f,-0.5f, 0.0f);
	channel->addAnyData(d1.data());
	auto d2 = math::vec3f_t( 0.0f, 0.5f, 0.0f);
	channel->addAnyData(d2.data());
	
	gapi::BufferCreateInfoSet bufferCreateInfoSet;
	bufferCreateInfoSet.vb.desc.target = gapi::BufferTarget_t::kArray;
	bufferCreateInfoSet.vb.desc.usage = gapi::BufferUsage_t::kStatic;
	bufferCreateInfoSet.vb.desc.byteStride = sizeof(math::VertexPosition);
	bufferCreateInfoSet.vb.desc.capacity = data->getVertexCount();
	bufferCreateInfoSet.vb.data = data->getRaw();

	_staticMesh = std::make_shared<graphics::StaticMesh>(renderSubqueue, _material, data, bufferCreateInfoSet);
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
