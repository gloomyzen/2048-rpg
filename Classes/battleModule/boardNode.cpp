#include "boardNode.h"

using namespace sr::battleModule;

boardNode::boardNode() {
	this->setName("boardNode");
	loadProperty("battleScene/" + this->getName(), dynamic_cast<Sprite*>(this));
	initBoard();
}

boardNode::~boardNode() {}

void boardNode::initBoard() {
	clearTiles();
	setDefaultPosition();
}

void boardNode::clearTiles() {
	///Destroy <- todo добавить красивый дестрой тайлов
	for (auto list : tileList) {
		list.clear();
		list.reserve(BOARD_COUNT_Y);
	}
	tileList.reserve(BOARD_COUNT_X);
}

void boardNode::setDefaultPosition() {
	cocos2d::Vec2 position;
	position.x = BOARD_START_POS_X;
	position.y = BOARD_START_POS_Y;
	for (int x = 0; x < BOARD_COUNT_X; ++x) {
		std::vector<sTileData> row{};
		for (int y = 0; y < BOARD_COUNT_Y; ++y) {
			if (y == 0) {
				position.y = BOARD_START_POS_Y;
			}
			sTileData data;
			data.pos = position;
			data.tile = new tileNode();
			data.tile->setPosition(data.pos);
			addChild(data.tile);
			position.y += BOARD_TILE_H;
			row.push_back(data);
		}
		tileList.push_back(row);
		position.x += BOARD_TILE_W;
	}
}
