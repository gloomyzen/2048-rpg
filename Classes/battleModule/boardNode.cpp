#include "boardNode.h"
#include "databaseModule/databaseManager.h"

using namespace sr::battleModule;

boardNode::boardNode() {
	this->setName("boardNode");
}

boardNode::~boardNode() {}

std::deque<nodeTasks> boardNode::getTasks() {
	std::deque<nodeTasks> result;

	result.emplace_back([this]() {
		loadProperty("battleScene/" + this->getName(), dynamic_cast<Sprite*>(this));
		return eTasksStatus::STATUS_OK;
	});

	return result;
}

void boardNode::initBoard() {
	clearTiles();
	setDefaultPosition();
	initHandling();
	//todo only for test, remove after testing
//	auto test = GET_DATABASE_MANAGER().getTileDatabase();
//	auto test2 = GET_DATABASE_MANAGER().getGameModesDB();
//	test2.executeLoadData();
//	auto testTool = gameModesTool::getNextTile(eGameMode::ENDLESS);
//	auto nextTile = gameModesTool::getNextTile(eGameMode::ENDLESS);
}

void boardNode::clearTiles() {
	///Destroy <- todo добавить анимацию дестроя тайлов
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
		std::vector<sTileNode*> row{};
		for (int y = 0; y < BOARD_COUNT_Y; ++y) {
			if (y == 0) {
				position.y = BOARD_START_POS_Y;
			}
			if (x == BOARD_HERO_POS_X && y == BOARD_HERO_POS_Y) {
				//todo init hero tile
			}
			auto data = new sTileNode();
			data->pos = position;
			data->tile = new tileNode();
			data->tile->setTileSize(boardTileWH, boardTileWH);
			data->tile->setPosition(data->pos);
			addChild(data->tile);
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
	//todo need calculate correct distance of swipe
	auto dir = eSwipeDirection::UNDEFINED;
	if (touch->getStartLocation().x > touch->getLocation().x && touch->getStartLocation().x - BOARD_TOUCH_FORCE > touch->getLocation().x) {
		CCLOG("boardNode::touchUpdate: Left swipe");
		dir = eSwipeDirection::LEFT;
	} else if (touch->getStartLocation().x < touch->getLocation().x && touch->getStartLocation().x + BOARD_TOUCH_FORCE < touch->getLocation().x) {
		CCLOG("boardNode::touchUpdate: Right swipe");
		dir = eSwipeDirection::RIGHT;
	} else if (touch->getStartLocation().y > touch->getLocation().y && touch->getStartLocation().y - BOARD_TOUCH_FORCE > touch->getLocation().y) {
		CCLOG("boardNode::touchUpdate: Down swipe");
		dir = eSwipeDirection::DOWN;
	} else if (touch->getStartLocation().y < touch->getLocation().y && touch->getStartLocation().y + BOARD_TOUCH_FORCE < touch->getLocation().y) {
		CCLOG("boardNode::touchUpdate: Up swipe");
		dir = eSwipeDirection::UP;
	}
	if (swipeClb && swipeClb(dir)) {
		CCLOG("boardNode::touchUpdate: Valid swipe");
	} else {
		CCLOG("boardNode::touchUpdate: Swipe is not valid");
	}
}

void boardNode::setHeroTileData(sTileData *heroTile) {
	hero = heroTile;
}
