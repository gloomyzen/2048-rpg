#include "tileNode.h"

using namespace sr::battleModule;

tileNode::tileNode() {
	this->setName("tileNode");
	loadProperty("battleScene/" + this->getName(), dynamic_cast<Sprite*>(this));
}
