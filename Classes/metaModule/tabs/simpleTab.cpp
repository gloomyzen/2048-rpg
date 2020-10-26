#include "simpleTab.h"

using namespace sr::metaModule;


simpleTab::simpleTab() {
	this->setName("simpleTab");
	loadProperty("menuScene/tabs/" + this->getName(), dynamic_cast<Node *>(this));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (auto label = dynamic_cast<Label *>(findNode("comingSoon", this))) {
		label->setPosition(visibleSize / 2);
	}

}

simpleTab::~simpleTab() = default;
