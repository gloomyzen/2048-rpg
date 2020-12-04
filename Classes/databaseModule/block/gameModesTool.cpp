#include "gameModesTool.h"
#include "common/debugModule/logManager.h"
#include "common/utilityModule/findUtility.h"
#include "common/utilityModule/randomUtility.h"
#include <vector>
#include <tuple>

using namespace sr::databaseModule;

gameModesTool::gameModesTool() {}

gameModesTool::~gameModesTool() {}

std::vector<sTileData*> gameModesTool::getNextTile(eGameMode mode) {
	auto gmDB = GET_DATABASE_MANAGER().getGameModesDB();
	gmDB.executeLoadData();
	auto currentMode = gmDB.getModeByType(mode);
	if (currentMode == nullptr) {
		LOG_ERROR(cocos2d::StringUtils::format("gameModesTool::getNextTile: Can't get next tile for mode: %d", static_cast<int>(mode)));
		return std::vector<sTileData *>();
	}
	//calculate chance to spawn
	if (currentMode->spawnPerSwipe.empty()) {
		LOG_ERROR(cocos2d::StringUtils::format("gameModesTool::getNextTile: Can't get next tile for mode: %d, spawnPerSwipe is empty!", static_cast<int>(mode)));
		return std::vector<sTileData *>();
	}
	int countSpawn = 0;
	{
		std::vector<std::pair<int, sSpawnChance*>> tempContainer;
		for (auto item : currentMode->spawnPerSwipe) {
			tempContainer.emplace_back(item->chance, item);
		}
		using namespace common::utilityModule;
		auto nextChance = findUtility::findClosest(randomUtility::generateBetween(1, 100), tempContainer);
		if (nextChance == nullptr) {
			LOG_ERROR(cocos2d::StringUtils::format("gameModesTool::getNextTile: Can't get next tile for mode: %d, can't get valid chance!", static_cast<int>(mode)));
			return std::vector<sTileData *>();
		}
		countSpawn = nextChance->count;
	}
	//get random tile from list
	std::vector<sTileData *> result{};
	{
		std::vector<std::pair<int, sSpawnTile*>> tempContainer;
		for (auto item : currentMode->tiles) {
			tempContainer.emplace_back(item->chance, item);
		}
		using namespace common::utilityModule;
		for(int i = 0; i < countSpawn; ++i) {
			auto nextTile = findUtility::findClosest(randomUtility::generateBetween(1, 100), tempContainer);
			result.push_back(nextTile->tile);
		}
	}
	return std::vector<sTileData *>();
}
