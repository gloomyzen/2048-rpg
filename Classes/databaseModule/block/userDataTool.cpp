#include "userDataTool.h"
#include "cocos2d.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/battleLevelsDB.h"
#include "databaseModule/databases/questsDB.h"
#include "common/utilityModule/randomUtility.h"

using namespace sr::databaseModule;
using namespace sr::profileModule;

userDataTool *currentUserDataInstance = nullptr;

userDataTool::userDataTool() {}

userDataTool::~userDataTool() {}

userDataTool &userDataTool::getInstance() {
	if (currentUserDataInstance == nullptr) {
		currentUserDataInstance = new userDataTool();
	}
	return *currentUserDataInstance;
}

std::vector<sLocationLog*> userDataTool::getLevelProfile(eBattleLevelsTypes type) {
	auto locationBlock = GET_PROFILE().getLocationBlock();
	auto currentLvl = locationBlock->getLogByLevel(type);

	auto questsDB = GET_DATABASE_MANAGER().getQuestsDB();
	questsDB.executeLoadData();

	auto battleDB = GET_DATABASE_MANAGER().getBattleLevelsDB();
	battleDB.executeLoadData();
	auto levelBlueprint = battleDB.getDataByLevel(type);


	for (const auto& item : levelBlueprint->currentMap) {
		auto data = item.second;
		auto profileLvl = std::find_if(currentLvl.begin(), currentLvl.end(), [data](sLocationLog* log){
			return log->id == data->id;
		});
		if (profileLvl != currentLvl.end()) {
			if ((*profileLvl)->questId == 0u) {
				(*profileLvl)->questId = common::utilityModule::randomUtility::getRandomVector<unsigned int>(data->quests);
			}
		} else {
			auto newLvl = new sLocationLog();
			newLvl->questId = common::utilityModule::randomUtility::getRandomVector<unsigned int>(data->quests);
			newLvl->id = data->id;
			currentLvl.push_back(newLvl);
		}
	}

	return currentLvl;
}


