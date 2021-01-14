#include "simpleTab.h"

using namespace sr::metaModule;


simpleTab::simpleTab() {
	this->setName("simpleTab");
	loadProperty("menuScene/tabs/" + this->getName(), dynamic_cast<Node *>(this));
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	if (auto label = dynamic_cast<cocos2d::Label *>(findNode("comingSoon"))) {
		label->setPosition(visibleSize / 2);
	}

}

simpleTab::~simpleTab() = default;
