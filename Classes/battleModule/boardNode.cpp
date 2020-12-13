#include "boardNode.h"
#include "databaseModule/databaseManager.h"
#include "common/debugModule/logManager.h"

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
	boardTileWH = boardSize.width / BOARD_COUNT_X;
	boardSize.height = boardTileWH * BOARD_COUNT_Y;
	this->setContentSize(boardSize);

	cocos2d::Vec2 position;
	position.x = BOARD_START_POS_X;
	position.y = BOARD_START_POS_Y;
	for (int x = 0; x < BOARD_COUNT_X; ++x) {
		std::map<int, sSlot*> row{};
		for (int y = 0; y < BOARD_COUNT_Y; ++y) {
			if (y == 0) {
				position.y = BOARD_START_POS_Y;
			}
			sSlot* slot;
			auto block = new Node();
			block->setName(StringUtils::format("block_%d_%d", x, y));
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
	heroData = heroTile;
}

void boardNode::scrollBoard(eSwipeDirection direction) {
	if (!spawnClb) {
		LOG_ERROR("boardNode::scrollBoard: Can't get next tile from spawn callback!");
		return;
	}
	if (direction == eSwipeDirection::UNDEFINED) {
		LOG_ERROR("boardNode::scrollBoard: Swipe direction is wrong!");
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
	bool isFirstTile;
	switch (direction) {
		case eSwipeDirection::UP: {
//			for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
//				for (int y = static_cast<int>(tileMap[x].size()) - 1; y >= 0; --y) {
//					//
//				}
//			}
			for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
				isFirstTile = true;
				for (int y = 0; y < static_cast<int>(tileMap[x].size()); ++y) {
					auto tempY = y - 1;
					//todo нужно доработать корректное определие конца поля и объединять фишки выходящие за диапазон этих значений
					if (isFirstTile) {
						isFirstTile = false;
					} else
					if (tempY >= 0 && tempY < BOARD_COUNT_Y) {
						if (tileMap[x][y]->isHero || tileMap[x][tempY]->isHero) {
							//todo hero swap
							continue;
						} else {
							tileMap[x][y]->block->removeChild(tileMap[x][y]->tile, false);
							tileMap[x][tempY]->block->removeChild(tileMap[x][tempY]->tile, false);
							if (tileMap[x][y]->tile != nullptr) {
								tileMap[x][tempY]->block->addChild(tileMap[x][y]->tile);
							}
							std::swap(tileMap[x][y]->tile, tileMap[x][tempY]->tile);
						}
					} else {
						//todo top row
					}
				}
			}
		}
			break;
		case eSwipeDirection::DOWN: {
//			for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
//				for (int y = 0; y < static_cast<int>(tileMap[x].size()); ++y) {
//					//
//				}
//			}
			for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
				for (int y = static_cast<int>(tileMap[x].size()) - 1; y >= 0; --y) {
					auto tempY = y + 1;
					if (tempY >= 0 && tempY < BOARD_COUNT_Y) {
						if (tileMap[x][y]->isHero || tileMap[x][tempY]->isHero) {
							//todo hero swap
							continue;
						} else {
							tileMap[x][y]->block->removeChild(tileMap[x][y]->tile, false);
							tileMap[x][tempY]->block->removeChild(tileMap[x][tempY]->tile, false);
							if (tileMap[x][y]->tile != nullptr) {
								tileMap[x][tempY]->block->addChild(tileMap[x][y]->tile);
							}
							std::swap(tileMap[x][y]->tile, tileMap[x][tempY]->tile);
						}
					} else {
						//todo top row
					}
				}
			}
		}
			break;
		case eSwipeDirection::LEFT: {
			for (int y = 0; y < static_cast<int>(tileMap[0].size()); ++y) {
				for (int x = 0; x < static_cast<int>(tileMap.size()); ++x) {
					//
				}
			}
		}
			break;
		case eSwipeDirection::RIGHT: {
			for (int y = 0; y < static_cast<int>(tileMap[0].size()); ++y) {
				for (int x = static_cast<int>(tileMap.size()) - 1; x >= 0; --x) {
					//
				}
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
			//todo insert tiles to tileMap
			auto tile = new tileNode();
			tile->setTileSize(boardTileWH, boardTileWH);
			tile->createTile(*(*it));
			tileMap[item.first][item.second]->block->addChild(tile);
			tileMap[item.first][item.second]->tile = tile;
			nextTiles.erase(it);
		} else {
			LOG_ERROR("boardNode::scrollBoard: Slot has parameters beyond the radius of the array!");
		}
	}


//	for (std::size_t x = 0; x < tileMap.size(); ++x) {
//		for (std::size_t y = 0; y < tileMap[x].size(); ++y) {
//
//		}
//	}

	//get list of free tiles
//	std::map<int, int> freeSlots;
//	for (std::size_t x = 0; x < tileMap.size(); ++x) {
//		for (std::size_t y = 0; y < tileMap[x].size(); ++y) {
//			if (tileMap[x][y] == nullptr) {
//				freeSlots.insert({x, y});
//			}
//		}
//	}

	for (std::size_t x = 0; x < tileMap.size(); ++x) {
		for (std::size_t y = 0; y < tileMap[x].size(); ++y) {
			auto item = tileMap[x][y];
			if (item->tile != nullptr && item->tile->getTileType() == eTileTypes::HERO) continue;
			auto test = getNeighborTail(direction, x, y);
			switch (direction) {
				case eSwipeDirection::UP: {
				}
					break;
				case eSwipeDirection::DOWN: {
				}
					break;
				case eSwipeDirection::LEFT: {
				}
					break;
				case eSwipeDirection::RIGHT: {
				}
					break;
				default: {
					LOG_ERROR("boardNode::scrollBoard: Can't swipe, wrong direction!");
					return;
				}
					break;
			}
		}
	}

}

void boardNode::update(float delta) {
	Node::update(delta);

	for (std::size_t x = 0; x < tileMap.size(); ++x) {
		for (std::size_t y = 0; y < tileMap[x].size(); ++y) {
			if (tileMap[x][y] == nullptr) {
				//todo На завтра
				// нужно создать экшен который сгенерит новый тайл вместо пустого
				// нужно делать корректное смещение тайлов через очистку контейнера в начале или в конце
				auto test = "";
			}
		}
	}
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
