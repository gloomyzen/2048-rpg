#include "questTool.h"
#include "common/utilityModule/randomUtility.h"

using namespace sr::databaseModule;

questTool::questTool() {}
questTool::~questTool() {}

std::vector<sQuestObjective*> questTool::getObjectives() {
	if (quests.empty()) {
		generateNextObjective();
	}

	return quests;
}

bool questTool::updateObjectives(eSwipeDirection direction) {
	bool wasChanged = false;
	for (auto &item : quests) {
		if (item->direction == direction) {
			if (item->leftSwipes >= 0) {
				wasChanged = true;
				item->leftSwipes -= 1;
			}
		}
	}

	return wasChanged;
}

void questTool::generateNextObjective() {
	auto nextItem = new sQuestObjective();
	auto nextId = common::utilityModule::randomUtility::generateBetween(1, 4);
	nextItem->direction = static_cast<eSwipeDirection>(nextId);
	quests.push_back(nextItem);
}