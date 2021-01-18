#include "soundButton.h"

using namespace sr::interfaceModule;

sr::interfaceModule::soundButton::soundButton() {
	listener = cocos2d::EventListenerTouchOneByOne::create();
}

soundButton::~soundButton() {
	Sprite::~Sprite();
}
