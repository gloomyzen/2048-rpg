#include "battleCore.h"
#include "databaseModule/databases/gameModesDB.h"
#include "databaseModule/block/gameModesTool.h"
#include "databaseModule/databases/gameEnums.h"
#include "interfaceModule/widgets/stateIconLabel.h"

using namespace sr::battleModule;
using namespace sr::interfaceModule;
using namespace sr::databaseModule;
using namespace cocos2d;
using namespace common;

battleCore::battleCore() {
	this->setName("battleNode");
	loadProperty("battleScene/" + this->getName(), this);
	board = new boardNode();
	board->executeTasks();
	questMgr = new questTool();
}

std::deque<nodeTasks> battleCore::getTasks() {
	std::deque<nodeTasks> result;

	result.emplace_back([this]() {
		questList = dynamic_cast<questPool*>(findNode("questList"));
		if (!questList) {
			LOG_ERROR("battleCore::getTasks() Can't find element 'questList'!");
			return eTasksStatus::STATUS_ERROR_BREAK;
		}
		//fixme пока что только один квест в один переод времени, в будущем переделаем
		auto quests = questMgr->getObjectives();
		questList->printQuest(quests.front());

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
		auto gameModeDb = GET_DATABASE_MANAGER().getGameModesDB();
		gameModeDb.executeLoadData();
		auto currentGameMode = gameModeDb.getModeByType(eGameMode::ENDLESS);
		board->setHeroTileData(currentGameMode->heroTile);
		board->initBoard();
		board->setSwipeCallback([=](eSwipeDirection direction){
			board->scrollBoard(direction);
			auto updated = questMgr->updateObjectives(direction);
			if (updated) {
				auto quest = questMgr->getObjectives().front();
				questList->printQuest(quest);
				if (quest->leftSwipes == 0) {
					//spawn quest tile

				}
			}
			return true;
		});
		board->setSpawnCallback([=](){
			return gameModesTool::getNextTile(eGameMode::ENDLESS);
		});

		board->setHeroMatchCallback([this](tileNode* tile){
			if (tile == nullptr) return false;
			auto data = tile->getTileData();
			if (data != nullptr) {
				switch (data->type) {
					case eTileTypes::HERO:
					case eTileTypes::UNDEFINED:
					case eTileTypes::EMPTY:
					case eTileTypes::ENVIRONMENT:
						break;
					case eTileTypes::ITEM: {
						currentHp += data->hp * tile->getCount();
						currentEnergy += data->attack * tile->getCount();
						updateStats();
						return true;
					}
						break;
					case eTileTypes::ENEMY:
						if (currentEnergy >= data->hp * tile->getCount()) {
							currentHp -= data->hp * tile->getCount();
							currentEnergy -= data->attack * tile->getCount();
							updateStats();
							return true;
						}
						tile->setCount(tile->getCount() - currentEnergy);
						currentHp -= data->attack * tile->getCount();
						updateStats();
						return false;
						break;
				}
			}
			return true;
		});

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
		clippingNode = ClippingNode::create();
		clippingNode->setName("boardClippingNode");
		loadComponent("battleScene/" + clippingNode->getName(), clippingNode);
		DrawNode *stencil = DrawNode::create();
		addChild(clippingNode);
		//for debug
//		 addChild(board);
		clippingNode->addChild(board);

		auto rect = board->getBoundingBox();
		auto parentSize = clippingNode->getContentSize();
		Vec2 origin = rect.origin;
		Vec2 destination;
		auto boardSize = board->getContentSize();
		origin.x = origin.x * board->getAnchorPoint().x;
		origin.y = origin.y * board->getAnchorPoint().y;
		destination.x = rect.origin.x + rect.size.width;
		destination.y = rect.origin.y + rect.size.height;

		stencil->setName("clipperStencil");
		stencil->drawSolidRect(origin, destination, Color4F::MAGENTA);
		//for debug
//		 addChild(stencil);
		clippingNode->setStencil(stencil);

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
		if (auto state = dynamic_cast<stateIconLabel*>(findNode("hpLbl"))) {
			hpLbl = state->getLabel();
		}
		if (auto state = dynamic_cast<stateIconLabel*>(findNode("energyLbl"))) {
			energyLbl = state->getLabel();
		}
		currentEnergy = 1;
		currentHp = 1;
		updateStats();

		return eTasksStatus::STATUS_OK;
	});

	return result;
}

void battleCore::updateStats() {
	if (hpLbl) {
		hpLbl->setString(std::to_string(currentHp));
	}
	if (energyLbl) {
		energyLbl->setString(std::to_string(currentEnergy));
	}
}
