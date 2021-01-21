#include "cocostudio/SimpleAudioEngine.h"
#include "scrollHolder.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/battleLevelsDB.h"
#include "databaseModule/databases/questsDB.h"
#include "profileModule/profileManager.h"
#include "databaseModule/block/userDataTool.h"
#include "common/debugModule/logManager.h"
#include "interfaceModule/widgets/soundButton.h"

using namespace sr::mapModule;
using namespace cocos2d;

scrollHolder::scrollHolder() {
	this->setName("scrollHolder");
	loadProperty(this->getName(), this);
}

scrollHolder::~scrollHolder() {}

std::deque<nodeTasks> scrollHolder::getTasks() {
	std::deque<nodeTasks> result;
	result.emplace_back([this]() {
//		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/menu.wav", true);
		scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
		//this is draft, only for prototype
		auto currentType = databaseModule::eBattleLevelsTypes::FOREST_LEVEL;

		auto profileData = databaseModule::userDataTool::getInstance().getLevelProfile(currentType);
		auto battleDB = GET_DATABASE_MANAGER().getBattleLevelsDB();
		battleDB.executeLoadData();
		auto levelBlueprint = battleDB.getDataByLevel(currentType);


		for (auto it = profileData.rbegin(); it != profileData.rend(); ++it) {
			auto currentPiece = levelBlueprint->getDataPieceById((*it)->id);
			if (!currentPiece->quests.empty()) {
				auto node = new nodeProperties<interfaceModule::soundButton>();
				node->setName(currentPiece->nodeName);
				node->setPosition(currentPiece->position);
				node->loadProperty(currentPiece->property, node);
				node->setName(STRING_FORMAT("mapPiece_%d_row%d", currentPiece->id, currentPiece->row));
				piecesList.push_back(new sMapPiece(currentPiece, *it, node));
				scrollView->addChild(node);
			} else {
				piecesList.push_back(new sMapPiece(currentPiece, *it, nullptr));
			}
		}
		return eTasksStatus::STATUS_OK;
	});

	return result;
}
