#include "boardNode.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/gameModesDB.h"

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
	initHandling();
	//todo only for test, remove after testing
//	auto test = GET_DATABASE_MANAGER().getTileDatabase();
	auto test2 = GET_DATABASE_MANAGER().getGameModesDB();
	test2.executeLoadData();
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
	cocos2d::Size boardSize;
	boardSize.width = Director::getInstance()->getVisibleSize().width;
	float boardTileWH = boardSize.width / BOARD_COUNT_X;
	boardSize.height = boardTileWH * BOARD_COUNT_Y;
	this->setContentSize(boardSize);

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
			data.tile = new tileNode(boardTileWH, boardTileWH);
			data.tile->setPosition(data.pos);
			addChild(data.tile);
			position.y += boardTileWH;
			row.push_back(data);
		}
		tileList.push_back(row);
		position.x += boardTileWH;
	}
}

void boardNode::initHandling() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event*){
		if (!isTouch) {
			isTouch = true;
			lastTouchInfo = touch;
			return true;
		}
		return false;
	};
//	listener->onTouchMoved = [](Touch*, Event*){ return true; };
	listener->onTouchEnded = [this](Touch* touch, Event* event){
		touchUpdate(touch, event);
		isTouch = false;
		return true;
	};
	listener->onTouchCancelled = [this](Touch* touch, Event* event){
		touchUpdate(touch, event);
		isTouch = false;
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void boardNode::touchUpdate(Touch* touch, Event* event) {
	//todo check distance and event
	if (touch->getStartLocation().x > touch->getLocation().x && touch->getStartLocation().x - BOARD_TOUCH_FORCE > touch->getLocation().x) {
		CCLOG("LEFT SWIPE");
	} else if (touch->getStartLocation().x < touch->getLocation().x && touch->getStartLocation().x + BOARD_TOUCH_FORCE < touch->getLocation().x) {
		CCLOG("RIGHT SWIPE");
	} else if (touch->getStartLocation().y > touch->getLocation().y && touch->getStartLocation().y - BOARD_TOUCH_FORCE > touch->getLocation().y) {
		CCLOG("DOWN SWIPE");
	} else if (touch->getStartLocation().y < touch->getLocation().y && touch->getStartLocation().y + BOARD_TOUCH_FORCE < touch->getLocation().y) {
		CCLOG("UP SWIPE");
	}
}
