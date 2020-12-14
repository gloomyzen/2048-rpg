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
	countLbl = dynamic_cast<Label*>(findNode("countLbl", this));
	if (hpIcon) hpIcon->setVisible(false);
	if (hpCountLbl) hpCountLbl->setVisible(false);
	if (attackCountLbl) attackCountLbl->setVisible(false);
	if (countLbl) countLbl->setVisible(false);
}

void tileNode::createTile(const sTileData &data) {
	tileData = new sTileData(data);
	tileType = tileData->type;
	if (tileData->tileUpgrade.empty()) {
		LOG_WARNING("tileNode::createTile: tile upgrade is empty!");
		return;
	}
	// find closest by level
	sTilesUpgrade* currentUpgrade = nullptr;
	for (auto item : tileData->tileUpgrade) {
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

	//draw count
	if (tileType != eTileTypes::HERO) {
		drawCount();
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

void tileNode::setCount(int count) {
	currentCnt = count;
	if (currentCnt < 0)
		currentCnt = 0;
	drawCount();
}

std::string tileNode::getTileDataName() {
	if (tileData) {
		return tileData->name;
	}
	return std::string();
}

void tileNode::drawCount() {
	if (countLbl) {
		countLbl->setString(std::to_string(currentCnt));
		if (currentCnt == 0) {
			countLbl->setVisible(false);
		} else {
			if (currentCnt > 99) {
				countLbl->setString("99+");
			} else {
			}
			countLbl->setVisible(true);
		}
	} else {
		LOG_WARNING("tileNode::drawCount: 'countLbl' node not found!");
	}
}
