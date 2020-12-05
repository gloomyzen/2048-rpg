#include "battleCore.h"
#include "databaseModule/databases/gameModesDB.h"
#include "databaseModule/block/gameModesTool.h"

using namespace sr::battleModule;

battleCore::battleCore() {
	this->setName("battleNode");
	loadProperty("battleScene/" + this->getName(), this);
	board = new boardNode();
	board->executeTasks();
}

std::deque<nodeTasks> battleCore::getTasks() {
	std::deque<nodeTasks> result;

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
		auto gameModeDb = GET_DATABASE_MANAGER().getGameModesDB();
		gameModeDb.executeLoadData();
		auto currentGameMode = gameModeDb.getModeByType(eGameMode::ENDLESS);
		//todo На завтра,
		// нужно отправить из мода героя на доску, нужно чтобы доска знала минимум, и держала только коллбеки
		// Далее нужно зарегистрировать из кора коллбек на свайп доски
		// Нужен метод для спавна при свайпе, зарегистрировать тоже из кора

		return eTasksStatus::STATUS_OK;
	});

	return result;
}
