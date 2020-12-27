#include "boardNode.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/gameEnums.h"
#include "common/debugModule/logManager.h"

using namespace sr::battleModule;
using namespace sr::databaseModule;
using namespace cocos2d;

boardNode::boardNode() {
	this->setName("boardNode");
}

boardNode::~boardNode() {}

std::deque<nodeTasks> boardNode::getTasks() {
	std::deque<nodeTasks> result;

	result.emplace_back([this]() {
		loadProperty("battleScene/" + this->getName(), this);
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
	for (const auto& row : tileMap) {
		for (auto tile : row.second) {
			delete tile.second;
			tile.second = nullptr;
		}
	}
}

void boardNode::setDefaultPosition() {
	cocos2d::Size boardSize;
	boardSize.width = Director::getInstance()->getVisibleSize().width;
	boardTileWH = (boardSize.width - BOARD_OFFSET_POS_X * 2) / BOARD_COUNT_X;
	boardSize.height = boardTileWH * BOARD_COUNT_Y + BOARD_OFFSET_POS_Y * 2;
	this->setContentSize(boardSize);

	cocos2d::Vec2 position;
	position.x = BOARD_START_POS_X + BOARD_OFFSET_POS_X;
	position.y = BOARD_START_POS_Y + BOARD_OFFSET_POS_Y;
	for (int x = 0; x < BOARD_COUNT_X; ++x) {
		std::map<int, sSlot*> row{};
		for (int y = 0; y < BOARD_COUNT_Y; ++y) {
			if (y == 0) {
				position.y = BOARD_START_POS_Y + BOARD_OFFSET_POS_Y;
			}
			sSlot* slot;
			auto block = new Node();
			block->setName(StringUtils::format("block_%d_%d", x, y));
			block->setContentSize(cocos2d::Size(boardTileWH, boardTileWH));
			addChild(block);
			block->setPosition(position);
			if (x == BOARD_HERO_POS_X && y == BOARD_HERO_POS_Y && heroData) {
				auto tile = new tileNode();
				tile->setTileSize(boardTileWH, boardTileWH);
				tile->createTile(*heroData);
				block->addChild(tile);
				slot = new sSlot(position, tile, true);
			} else {
				slot = new sSlot(position, nullptr);
			}
			slot->block = block;
			position.y += boardTileWH;
			row.insert({y, slot});
		}
		tileMap.insert({x, row});
		position.x += boardTileWH;
	}
	generateBoardBg(Vec2(BOARD_START_POS_X + BOARD_OFFSET_POS_X, BOARD_START_POS_Y + BOARD_OFFSET_POS_Y));
	auto border = dynamic_cast<Sprite*>(findNode("border"));
	border->setContentSize(cocos2d::Size(boardTileWH * BOARD_COUNT_X + BOARD_OFFSET_POS_X * 2, boardTileWH * BOARD_COUNT_Y + BOARD_OFFSET_POS_Y * 2));
}

void boardNode::generateBoardBg(Vec2 pos) {
	auto sliceX = BOARD_COUNT_PATTERN_X % BOARD_COUNT_X / 2;
	auto sliceY = BOARD_COUNT_PATTERN_Y % BOARD_COUNT_Y / 2;
	boardBgPos = Vec2(pos.x - sliceX * boardTileWH, pos.y - sliceY * boardTileWH);
	boardBg = Sprite::create();
	boardBg->setName("bg");
	loadComponent("battleScene/" + this->getName(), dynamic_cast<Sprite*>(boardBg));
	boardBg->setPosition(boardBgPos);
	boardBg->setContentSize(cocos2d::Size(BOARD_COUNT_PATTERN_X * boardTileWH, BOARD_COUNT_PATTERN_Y * boardTileWH));
	addChild(boardBg, -1);
}

void boardNode::swipeBoardBg(eSwipeDirection direction) {
	Vec2 startPos = boardBgPos;
	startPos.x = boardBgPos.x + boardTileWH * (boardSolid ? 1 : 2);
	startPos.y = boardBgPos.y + boardTileWH * (boardSolid ? 1 : 2);
	Vec2 nextPos = boardBgPos;
	nextPos.x = boardBgPos.x + boardTileWH * (boardSolid ? 1 : 2);
	nextPos.y = boardBgPos.y + boardTileWH * (boardSolid ? 1 : 2);
	boardSolid = !boardSolid;
	switch (direction) {
		case eSwipeDirection::UNDEFINED:
			break;
		case eSwipeDirection::UP: {
			startPos.y = boardBgPos.y;
			nextPos.y = boardBgPos.y - boardTileWH;
		}
			break;
		case eSwipeDirection::DOWN: {
			startPos.y = boardBgPos.y;
			nextPos.y = boardBgPos.y + boardTileWH;
		}
			break;
		case eSwipeDirection::RIGHT: {
			startPos.x = boardBgPos.x;
			nextPos.x = boardBgPos.x - boardTileWH;
		}
			break;
		case eSwipeDirection::LEFT: {
			startPos.x = boardBgPos.x;
			nextPos.x = boardBgPos.x + boardTileWH;
		}
			break;
	}
	boardBg->setPosition(startPos);
	auto moveAction = MoveTo::create(BOARD_ANIMATION_DURATION, nextPos);
	boardBg->runAction(moveAction);
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
	if (dir != eSwipeDirection::UNDEFINED) {
		if (swipeClb && swipeClb(dir)) {
			CCLOG("boardNode::touchUpdate: Valid swipe");
		} else {
			CCLOG("boardNode::touchUpdate: Swipe is not valid");
		}
	}
}

void boardNode::setHeroTileData(sTileData *heroTile) {
	heroData = heroTile;
}

void boardNode::scrollBoard(eSwipeDirection direction) {
	if (!spawnClb) {
		LOG_ERROR("boardNode::scrollBoard: Can't get next tile from spawn callback!");
		return;
	}

	//проверяем соседние тайлы от героя, доступен ли свайп впринципе зависит от соседних клеток в первую очередь
	auto heroNeighborType = getNeighborTail(direction, BOARD_HERO_POS_X, BOARD_HERO_POS_Y);
	if (heroNeighborType == eTileTypes::ENEMY) {
		//todo battle logic
		//return;
	}

	//get list of free tiles
	std::vector<std::pair<int, int>> freeSlots;
	bool slotExist;
	bool heroFounded;
	switch (direction) {
		case eSwipeDirection::UNDEFINED: {
			LOG_ERROR("boardNode::scrollBoard: Swipe direction is wrong!");
			return;
		}
			break;
		case eSwipeDirection::UP: {
			for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
				heroFounded = false;
				slotExist = false;
				for (int y = static_cast<int>(tileMap[x].size()) - 1; y >= 0; --y) {
					if (heroFounded) continue;
					if (tileMap[x][y]->isHero) {
						heroFounded = true;
					} else if (tileMap[x][y]->tile == nullptr) {
						slotExist = true;
					}
				}
				if (slotExist) {
					freeSlots.emplace_back(x, static_cast<int>(tileMap[x].size()) - 1);
				}
			}
		}
			break;
		case eSwipeDirection::DOWN: {
			for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
				heroFounded = false;
				slotExist = false;
				for (int y = 0; y < static_cast<int>(tileMap[x].size()); ++y) {
					if (heroFounded) continue;
					if (tileMap[x][y]->isHero) {
						heroFounded = true;
					} else if (tileMap[x][y]->tile == nullptr) {
						slotExist = true;
					}
				}
				if (slotExist) {
					freeSlots.emplace_back(x, 0);
				}
			}
		}
			break;
		case eSwipeDirection::LEFT: {
			for (int y = 0; y < static_cast<int>(tileMap[0].size()); ++y) {
				heroFounded = false;
				slotExist = false;
				for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
					if (heroFounded) continue;
					if (tileMap[x][y]->isHero) {
						heroFounded = true;
					} else if (tileMap[x][y]->tile == nullptr) {
						slotExist = true;
					}
				}
				if (slotExist) {
					freeSlots.emplace_back(0, y);
				}
			}
		}
			break;
		case eSwipeDirection::RIGHT: {
			for (int y = 0; y < static_cast<int>(tileMap[0].size()); ++y) {
				heroFounded = false;
				slotExist = false;
				for (int x = static_cast<int>(tileMap.size()) - 1; x >= 0; --x) {
					if (heroFounded) continue;
					if (tileMap[x][y]->isHero) {
						heroFounded = true;
					} else if (tileMap[x][y]->tile == nullptr) {
						slotExist = true;
					}
				}
				if (slotExist) {
					freeSlots.emplace_back(static_cast<int>(tileMap.size()) - 1, y);
				}
			}
		}
			break;
	}

	//swap logic for all tiles
	swipeBoardBg(direction);
	switch (direction) {
		case eSwipeDirection::UNDEFINED:
			break;
		case eSwipeDirection::UP: {
			for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
				std::vector<sSlot*> elements;
				for (int y = 0; y < static_cast<int>(tileMap[x].size()); ++y) {
					elements.push_back(tileMap[x][y]);
				}
				swipeElements(elements);
			}
		}
			break;
		case eSwipeDirection::DOWN: {
			for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
				std::vector<sSlot*> elements;
				for (int y = static_cast<int>(tileMap[x].size()) - 1; y >= 0; --y) {
					elements.push_back(tileMap[x][y]);
				}
				swipeElements(elements);
			}
		}
			break;
		case eSwipeDirection::LEFT: {
			for (int y = 0; y < static_cast<int>(tileMap[0].size()); ++y) {
				std::vector<sSlot*> elements;
				for (int x = static_cast<int>(tileMap.size()) - 1; x >= 0; --x) {
					elements.push_back(tileMap[x][y]);
				}
				swipeElements(elements);
			}
		}
			break;
		case eSwipeDirection::RIGHT: {
			for (int y = 0; y < static_cast<int>(tileMap[0].size()); ++y) {
				std::vector<sSlot*> elements;
				for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
					elements.push_back(tileMap[x][y]);
				}
				swipeElements(elements);
			}
		}
			break;
	}

	auto nextTiles = spawnClb();

	if (freeSlots.size() > 1) {
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(freeSlots.begin(), freeSlots.end(), g);
	}

	for (auto item : freeSlots) {
		auto it = nextTiles.begin();
		if (it == nextTiles.end()) continue;
		if (item.first >= 0 && item.first < BOARD_COUNT_X
			&& item.second >= 0 && item.second < BOARD_COUNT_Y) {
			auto tile = new tileNode();
			tile->setTileSize(boardTileWH, boardTileWH);
			tile->createTile(*(*it));
			tileMap[item.first][item.second]->block->addChild(tile);
			tileMap[item.first][item.second]->tile = tile;
			auto originalScale = tile->getScale();
			tile->setScale(originalScale * .2f);
			auto scaleAction = ScaleTo::create(BOARD_ANIMATION_DURATION, originalScale);
			tile->runAction(scaleAction);
			nextTiles.erase(it);
		} else {
			LOG_ERROR("boardNode::scrollBoard: Slot has parameters beyond the radius of the array!");
		}
	}

}

void boardNode::update(float delta) {
	Node::update(delta);
}

eTileTypes boardNode::getNeighborTail(eSwipeDirection direction, int x, int y) {
	auto result = eTileTypes::UNDEFINED;

	switch (direction) {

		case eSwipeDirection::UNDEFINED: {
			LOG_ERROR("boardNode::getNeighborTail: Can't swipe, wrong direction!");
			return result;
		}
			break;
		case eSwipeDirection::UP: y += 1;
			break;
		case eSwipeDirection::DOWN: y -= 1;
			break;
		case eSwipeDirection::LEFT: x -= 1;
			break;
		case eSwipeDirection::RIGHT: x += 1;
			break;
	}

	if (x >= 0 && x < BOARD_COUNT_X
		&& y >= 0 && y < BOARD_COUNT_Y) {
		auto item = tileMap[x][y];
		if (item->tile != nullptr) {
			return item->tile->getTileType();
		}
	}

	return result;
}

std::pair<int, int> boardNode::getOffsetByDirection(eSwipeDirection direction, int x, int y) {
	std::pair<int, int> position = {x, y};
	switch (direction) {
		case eSwipeDirection::UP: position.second += 1;
			break;
		case eSwipeDirection::DOWN: position.second -= 1;
			break;
		case eSwipeDirection::LEFT: position.first -= 1;
			break;
		case eSwipeDirection::RIGHT: position.first += 1;
			break;
		case eSwipeDirection::UNDEFINED: {
			LOG_ERROR("boardNode::getNeighborTail: Can't swipe, wrong direction!");
			return position;
		}
			break;
	}

	return position;
}

void boardNode::swipeElements(std::vector<sSlot *> elements) {
	for (int i = 0; i < elements.size(); ++i) {
		auto currentItem = elements[i];
		auto hasNextItem = elements.size() > 1 && i < elements.size() - 1;

		if (currentItem->tile != nullptr && hasNextItem && elements[i + 1]->tile != nullptr) {
			//swap logic
			auto nextItem = elements[i + 1];
			if (nextItem->isHero) {
				continue;
			}
			if (currentItem->isHero) {
				if (heroMatchClb && heroMatchClb(nextItem->tile)) {
					//eat
					nextItem->block->removeChild(nextItem->tile, true);
					delete nextItem->tile;
					nextItem->tile = nullptr;
					auto originalScale = currentItem->tile->getScale();
					currentItem->tile->setScale(originalScale * 1.2f);
					auto scaleAction = ScaleTo::create(BOARD_ANIMATION_DURATION, originalScale);
					currentItem->tile->runAction(scaleAction);
				} else {
					//todo
//					one animation and destroy
				}
				continue;
			}
			if (currentItem->tile->canMatchTile(nextItem->tile)) {
				currentItem->tile->calculateCount(nextItem->tile);
				nextItem->block->removeChild(nextItem->tile, true);
				delete nextItem->tile;
				nextItem->tile = nullptr;
				auto originalScale = currentItem->tile->getScale();
				currentItem->tile->setScale(originalScale * 1.2f);
				auto scaleAction = ScaleTo::create(BOARD_ANIMATION_DURATION, originalScale);
				currentItem->tile->runAction(scaleAction);
			}
		} else if (currentItem->tile == nullptr && hasNextItem && elements[i + 1]->tile != nullptr) {
			//simple swipe
			auto nextItem = elements[i + 1];
			if (currentItem->isHero || nextItem->isHero) {
				continue;
			}
			auto prevPos = nextItem->block->convertToWorldSpaceAR(nextItem->tile->getPosition());
			nextItem->block->removeChild(nextItem->tile, false);
			std::swap(currentItem->tile, nextItem->tile);
			currentItem->block->addChild(currentItem->tile);
			{
				//move
				auto nextPos = currentItem->block->convertToNodeSpaceAR(prevPos);
				currentItem->tile->setPosition(nextPos);
				auto moveAction = MoveTo::create(BOARD_ANIMATION_DURATION, Vec2::ZERO);
				currentItem->tile->runAction(moveAction);
			}
		} else if (currentItem->tile != nullptr && !hasNextItem) {
			//nothing...
			//may be used in future
		}
	}
}
