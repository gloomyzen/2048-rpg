#include "boardNode.h"

using namespace sr::battleModule;

#define BOARD_START_POS_X 15
#define BOARD_START_POS_Y 12
#define BOARD_COUNT_X 5
#define BOARD_COUNT_Y 5
#define BOARD_TILE_W 148
#define BOARD_TILE_H 148

boardNode::boardNode() {
	this->setName("boardNode");
	loadProperty("battleScene/" + this->getName(), dynamic_cast<Sprite*>(this));
//	auto tile = new tileNode();
//	addChild(tile);
	initBoard();
}

boardNode::~boardNode() {

}

void boardNode::initBoard() {
	///Destroy <- todo добавить красивый дестрой тайлов
	tileList.clear();
	///Generate new board
	cocos2d::Vec2 position;
	position.x = BOARD_START_POS_X;
	position.y = BOARD_START_POS_Y;
	for (int x = 0; x < BOARD_COUNT_X; ++x) {
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
			tileList.push_back(data);
		}
		position.x += BOARD_TILE_W;
	}
}
