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

sLocationLog *userDataTool::getLevelProfile(eBattleLevelsTypes type) {
	auto locationBlock = GET_PROFILE().getLocationBlock();
	auto currentLvl = locationBlock->getLogByLevel(type);

	auto questsDB = GET_DATABASE_MANAGER().getQuestsDB();
	questsDB.executeLoadData();

//	questsDB.getQuestById(this is id...)


	return nullptr;
}


