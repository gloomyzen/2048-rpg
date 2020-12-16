#include "testWidget.h"

using namespace sr::interfaceModule;
using namespace cocos2d;


testWidget::testWidget() {
	this->setName("testWidget");
	loadProperty(this->getName(), dynamic_cast<Node*>(this));
}

testWidget::~testWidget() {}
