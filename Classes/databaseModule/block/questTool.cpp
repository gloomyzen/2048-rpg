#include "questTool.h"
#include "common/utilityModule/randomUtility.h"
#include "databaseModule/databaseManager.h"

using namespace sr::databaseModule;

questTool::questTool() {}
questTool::~questTool() {}

std::vector<sQuestObjective*> questTool::getObjectives() {
	if (quests.empty()) {
		generateNextObjective();
	}

	return quests;
}

void questTool::updateObjectives(eSwipeDirection direction) {
	checkEndObjectives();

	for (auto &item : quests) {
		if (item->direction == direction) {
			if (item->leftSwipes > 0) {
				item->leftSwipes -= 1;
			}
		}
	}
}

void questTool::checkEndObjectives() {
	bool mark = false;
	for (auto item : quests) {
		if (item->getDestroy()) {
			mark = true;
		}
	}
	if (mark) {
		quests.clear();
	}
	if (quests.empty()) {
		generateNextObjective();
	}
}

bool questTool::clearQuests() {
	quests.clear();
}

void questTool::generateNextObjective() {
	auto nextItem = new sQuestObjective();
	auto nextId = common::utilityModule::randomUtility::generateBetween(1, 4);
	nextItem->direction = static_cast<eSwipeDirection>(nextId);
	auto tileDb = GET_DATABASE_MANAGER().getTileDatabase();
	tileDb.executeLoadData();
	auto tile = tileDb.getTileByName("questItem1");
	nextItem->tile = tile;
	quests.push_back(nextItem);
}