#include "userDataTool.h"
#include "cocos2d.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/battleLevelsDB.h"
#include "databaseModule/databases/questsDB.h"

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


//	for (const auto& item : levelBlueprint->currentMap) {
//		auto [_, data] = item;
//		item.second.
//	}
	//todo foreach by levelBlueprint
//	if (currentLvl->questId == 0u) {
//		levelBlueprint->currentMap.
//	}


//	questsDB.getQuestById(this is id...)


	return currentLvl;
}


