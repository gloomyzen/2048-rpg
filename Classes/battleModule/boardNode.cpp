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
	this->scheduleUpdate();
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
		std::vector<sSlot*> row{};
		for (int y = 0; y < BOARD_COUNT_Y; ++y) {
			if (y == 0) {
				position.y = BOARD_START_POS_Y;
			}
			sSlot* slot;

			if (x == BOARD_HERO_POS_X && y == BOARD_HERO_POS_Y && hero) {
				auto tile = new tileNode();
				tile->setTileSize(boardTileWH, boardTileWH);
				tile->setPosition(position);
				tile->createTile(*hero);
				addChild(tile);
				slot = new sSlot(position, tile, true);
			} else {
				slot = new sSlot(position, nullptr);
			}
			position.y += boardTileWH;
			row.push_back(slot);
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

void boardNode::scrollBoard(eSwipeDirection direction) {
//	tileList[0][0];

	for (std::size_t x = 0; x < tileList.size(); ++x) {
		for (std::size_t y = 0; y < tileList[x].size(); ++y) {
			auto item = tileList[x][y];
//			cocos2d::Vec2 nextPos = item->getPosition();
			bool markToDestroy = false;
			switch (direction) {
				case eSwipeDirection::UP: {
//					if (y + 1 < tileList[x].size())
//						nextPos = positionsList[x][y + 1];
//					else
//						markToDestroy = true;
				}
					break;
				case eSwipeDirection::DOWN: {
//					if (y - 1 < tileList[x].size())
//						nextPos = positionsList[x][y - 1];
//					else
//						markToDestroy = true;
				}
					break;
				case eSwipeDirection::LEFT: {
//					if (x - 1 < tileList.size())
//						nextPos = positionsList[x - 1][y];
//					else
//						markToDestroy = true;
				}
					break;
				case eSwipeDirection::RIGHT: {
//					if (x + 1 < tileList.size())
//						nextPos = positionsList[x + 1][y];
//					else
//						markToDestroy = true;
				}
					break;
				default:
					break;
			}
			if (!markToDestroy) {
//				auto moveBy = MoveTo::create(0.5f, nextPos);
//				item->runAction(moveBy);
			} else {
//				tileList[x][y]->removeFromParentAndCleanup(true);
//				delete tileList[x][y];
//				tileList[x][y] = nullptr;
			}
		}
	}

}

void boardNode::update(float delta) {
	Node::update(delta);

	for (std::size_t x = 0; x < tileList.size(); ++x) {
		for (std::size_t y = 0; y < tileList[x].size(); ++y) {
			if (tileList[x][y] == nullptr) {
				//todo На завтра
				// нужно создать экшен который сгенерит новый тайл вместо пустого
				// нужно делать корректное смещение тайлов через очистку контейнера в начале или в конце
				auto test = "";
			}
		}
	}
}
