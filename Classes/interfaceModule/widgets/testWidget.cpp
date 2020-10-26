#include "testWidget.h"

using namespace sr::interfaceModule;


testWidget::testWidget() {
	this->setName("testWidget");
	loadProperty(this->getName(), dynamic_cast<Node*>(this));
}

testWidget::~testWidget() {}
