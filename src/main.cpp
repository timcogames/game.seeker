#include <sway/game.h>
#include <sway/ois.h>
#include <menustate.h>
#include <playstate.h>

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared

using namespace sway;

int main(int argc, char * argv[]) {
	auto framework = boost::make_shared<game::Framework>();
	framework->getInput()->registerDevice<ois::Keyboard>();
	framework->getInput()->registerDevice<ois::Mouse>();
	framework->startup(MenuState::getInstance());
	framework->run();
	return 0;
}
