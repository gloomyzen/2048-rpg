#include "stateIconLabel.h"

using namespace sr::interfaceModule;

stateIconLabel::stateIconLabel() {}

void stateIconLabel::initWithProp(std::string path) {
	this->setName(path);
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}

stateIconLabel* stateIconLabel::generateEnergyLabel() {
	auto widget = new stateIconLabel();
	widget->initWithProp("stateEnergyLabel");
	return widget;
}

stateIconLabel* stateIconLabel::generateHealthLabel() {
	auto widget = new stateIconLabel();
	widget->initWithProp("stateHealthLabel");
	return widget;
}

cocos2d::Label* stateIconLabel::getLabel() {
	if (auto label = dynamic_cast<cocos2d::Label*>(findNode("lbl"))) {
		return label;
	}
	return nullptr;
}
