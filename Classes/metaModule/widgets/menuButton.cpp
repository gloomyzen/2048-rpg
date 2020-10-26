#include "menuButton.h"

using namespace sr::metaModule;

menuButton::menuButton() {
	this->setName("menuButton");
	loadProperty("menuScene/widgets/" + this->getName(), dynamic_cast<Button*>(this));
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	if (auto label = dynamic_cast<Label*>(findNode("comingSoon", this))) {
//		label->setPosition(visibleSize / 2);
//	}
}

menuButton::~menuButton() = default;
