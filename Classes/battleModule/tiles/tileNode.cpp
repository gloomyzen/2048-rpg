#include "tileNode.h"
#include "common/debugModule/logManager.h"
#include "common/coreModule/nodes/spriteParameters.h"

using namespace sr::battleModule;

tileNode::tileNode() {
	this->setName("tileNode");
	loadProperty("battleScene/" + this->getName(), this);
	hpIcon = dynamic_cast<Sprite*>(findNode("hpIcon"));
	hpCountLbl = dynamic_cast<Label*>(findNode("hpCountLbl"));
	attackCountLbl = dynamic_cast<Label*>(findNode("attackCountLbl"));
	imgSlot = dynamic_cast<Node*>(findNode("imageSlot"));
	countLbl = dynamic_cast<Label*>(findNode("countLbl"));
	if (hpIcon) hpIcon->setVisible(false);
	if (hpCountLbl) hpCountLbl->setVisible(false);
	if (attackCountLbl) attackCountLbl->setVisible(false);
	if (countLbl) countLbl->setVisible(false);
}

void tileNode::createTile(const sTileData &data) {
	tileData = new sTileData(data);
	tileType = tileData->type;

	updateTileFromData();

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
	if (auto bg = dynamic_cast<Sprite*>(findNode("bg"))) {
		bg->setContentSize(tileSize);
	}
}

void tileNode::setCount(int count) {
	currentCnt = count;
	if (currentCnt < 0)
		currentCnt = 0;
	updateTileFromData();
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

void tileNode::calculateCount(tileNode* externalTile) {
	if (!canMatchTile(externalTile))
		return;
	auto count = externalTile->getCount();
	setCount(currentCnt + count);
}

bool tileNode::canMatchTile(tileNode* externalTile) {
	return externalTile != nullptr && externalTile->getTileDataName() == getTileDataName();
}

void tileNode::updateTileFromData() {
	if (tileData->tileUpgrade.empty()) {
		LOG_WARNING("tileNode::createTile: tile upgrade is empty!");
		return;
	}
	// find closest by level
	sTilesUpgrade* currentUpgrade = nullptr;
	for (auto item : tileData->tileUpgrade) {
		if (currentCnt <= item.first) {
			currentUpgrade = item.second;
		}
	}
	if (currentUpgrade == nullptr) {
		LOG_WARNING("tileNode::createTile: tile upgrade has no data in first key!");
		return;
	}
	//set bg
	if (!currentUpgrade->bg.empty()) {
		if (auto bg = dynamic_cast<Sprite*>(findNode("bg"))) {
			bg->initWithFile(currentUpgrade->bg);
			common::coreModule::spriteParameters::setCorrectPixelartTexture(bg);
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
		common::coreModule::spriteParameters::setCorrectPixelartTexture(icon);
		imgSlot->removeAllChildren();
		imgSlot->addChild(icon);
	}
}
