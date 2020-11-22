#include "tileNode.h"

using namespace sr::battleModule;

tileNode::tileNode() {
	this->setName("tileNode");
	loadProperty("battleScene/" + this->getName(), dynamic_cast<Sprite*>(this));
}

tileNode::tileNode(float w, float h) : tileNode() {
	cocos2d::Size tileSize;
	tileSize.width = w;
	tileSize.height = h;
	this->setContentSize(tileSize);
}

void tileNode::createTile(eTileType _type) {
	type = _type;
}
