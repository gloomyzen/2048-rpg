#include "stateIconLabel.h"

using namespace sr::interfaceModule;

stateIconLabel::stateIconLabel() {
	this->setName("stateIconLabel");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
}
