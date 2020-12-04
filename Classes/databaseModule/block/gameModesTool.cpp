#include "gameModesTool.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/findUtility.h"
#include <vector>
#include <tuple>

using namespace sr::databaseModule;

gameModesTool::gameModesTool() {}

gameModesTool::~gameModesTool() {}

sTileData* gameModesTool::getNextTile(eGameMode mode) {
	auto gmDB = GET_DATABASE_MANAGER().getGameModesDB();
	gmDB.executeLoadData();
	auto currentMode = gmDB.getModeByType(mode);
	if (currentMode == nullptr) {
		LOG_ERROR(cocos2d::StringUtils::format("gameModesTool::getNextTile: Can't get next tile for mode: %d", static_cast<int>(mode)));
		return nullptr;
	}
	//calculate chance to spawn
	if (currentMode->spawnPerSwipe.empty()) {
		LOG_ERROR(cocos2d::StringUtils::format("gameModesTool::getNextTile: Can't get next tile for mode: %d, spawnPerSwipe is empty!", static_cast<int>(mode)));
		return nullptr;
	}
	{
		std::vector<std::pair<int, sSpawnChance*>> tempContainer;
		for (auto item : currentMode->spawnPerSwipe) {
			tempContainer.emplace_back(item->percent, item);
		}
		using namespace common::utilityModule;
		auto res = findUtility::findClosest(2, tempContainer);
		auto test = "";
	}
	//get random tile from list
	return nullptr;
}


//int gameModesTool::findClosest(int roll, std::map<int, std::vector<characterInfo *>> items) {
//	std::vector<int> allChances{};
//	allChances.reserve(items.size());
//	for (auto &chance : items) {
//		allChances.emplace_back(chance.first);
//	}
//
//	int res = 0, diff = 0;
//	for (std::size_t i = 0; i < allChances.size(); ++i) {
//		if (i == 0 || std::abs(roll - allChances[i]) < diff) {
//			res = allChances[i];
//			diff = std::abs(roll - allChances[i]);
//		}
//	}
//	return res;
//}
