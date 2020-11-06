#include "boardNode.h"

using namespace sr::battleModule;

boardNode::boardNode() {
	this->setName("boardNode");
	loadProperty("battleScene/" + this->getName(), dynamic_cast<Sprite*>(this));
}

boardNode::~boardNode() {

}
