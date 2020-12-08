#include "tileNode.h"
#include "common/debugModule/logManager.h"

using namespace sr::battleModule;

tileNode::tileNode() {
	this->setName("tileNode");
	loadProperty("battleScene/" + this->getName(), this);
	hpIcon = dynamic_cast<Sprite*>(findNode("hpIcon", this));
	hpCountLbl = dynamic_cast<Label*>(findNode("hpCountLbl", this));
	attackCountLbl = dynamic_cast<Label*>(findNode("attackCountLbl", this));
	imgSlot = dynamic_cast<Node*>(findNode("imageSlot", this));
	if (hpIcon) hpIcon->setVisible(false);
	if (hpCountLbl) hpCountLbl->setVisible(false);
	if (attackCountLbl) attackCountLbl->setVisible(false);
}

void tileNode::createTile(const sTileData &data) {
	currentType = new sTileData(data);
	if (currentType->tileUpgrade.empty()) {
		LOG_WARNING("tileNode::createTile: tile upgrade is empty!");
		return;
	}
	// find closest by level
	sTilesUpgrade* currentUpgrade = nullptr;
	for (auto item : currentType->tileUpgrade) {
		if (currentLevel <= item.first) {
			currentUpgrade = item.second;
		}
	}
	if (currentUpgrade == nullptr) {
		LOG_WARNING("tileNode::createTile: tile upgrade has no data in first key!");
		return;
	}
	//set bg
	if (!currentUpgrade->bg.empty()) {
		if (auto bg = dynamic_cast<Sprite*>(findNode("bg", this))) {
			bg->initWithFile(currentUpgrade->bg);
			cocos2d::Size tileSize;
			tileSize.width = width;
			tileSize.height = height;
			bg->setContentSize(tileSize);
		} else {
			LOG_WARNING("tileNode::createTile: 'bg' node not found!");
			return;
		}
	}
	//set icon
	if (!currentUpgrade->icon.empty()) {
		auto icon = new Sprite();
		icon->initWithFile(currentUpgrade->icon);
		imgSlot->addChild(icon);
	}

}

void tileNode::setTileSize(float w, float h) {
	cocos2d::Size tileSize;
	tileSize.width = w;
	tileSize.height = h;
	width = w;
	height = h;
	this->setContentSize(tileSize);
	if (auto bg = dynamic_cast<Sprite*>(findNode("bg", this))) {
		bg->setContentSize(tileSize);
	}
}
