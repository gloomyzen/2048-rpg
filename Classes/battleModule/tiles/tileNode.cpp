#include "tileNode.h"

using namespace sr::battleModule;

tileNode::tileNode() {
	this->setName("tileNode");
	loadProperty("battleScene/" + this->getName(), this);
	hpIcon = dynamic_cast<Sprite*>(findNode("hpIcon", this));
	hpCountLbl = dynamic_cast<Label*>(findNode("hpCountLbl", this));
	attackCountLbl = dynamic_cast<Label*>(findNode("attackCountLbl", this));
	if (hpIcon) hpIcon->setVisible(false);
	if (hpCountLbl) hpCountLbl->setVisible(false);
	if (attackCountLbl) attackCountLbl->setVisible(false);
}

void tileNode::createTile(const sTileData &data) {
	currentType = new sTileData(data);
}

void tileNode::setTileSize(float w, float h) {
	cocos2d::Size tileSize;
	tileSize.width = w;
	tileSize.height = h;
	this->setContentSize(tileSize);
	if (auto bg = dynamic_cast<Sprite*>(findNode("bg", this))) {
		bg->setContentSize(tileSize);
	}
}
