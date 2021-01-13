#include "cocostudio/SimpleAudioEngine.h"
#include "scrollHolder.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/battleLevelsDB.h"
#include "databaseModule/databases/questsDB.h"
#include "profileModule/profileManager.h"
#include "databaseModule/block/userDataTool.h"

using namespace sr::mapModule;
using namespace cocos2d;

scrollHolder::scrollHolder() {
	this->setName("scrollHolder");
	loadProperty("mapScene/" + this->getName(), this);
}

scrollHolder::~scrollHolder() {}

std::deque<nodeTasks> scrollHolder::getTasks() {
	std::deque<nodeTasks> result;
	result.emplace_back([this]() {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/menu.wav", true);
		scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));
		//todo scroll by progress
//		auto bg = dynamic_cast<Sprite*>(findNode("bg"));
//		scrollView->setInnerContainerSize( cocos2d::Size(bg->getBoundingBox().size.width, bg->getBoundingBox().size.height));
//		scrollView->jumpToPercentBothDirection(Vec2(50.f, 50.f));
//		bg->setMarkDirty();

//		auto battleDB = GET_DATABASE_MANAGER().getBattleLevelsDB();
//		battleDB.executeLoadData();

//		auto locationBlock = GET_PROFILE().getLocationBlock();

		auto data = databaseModule::userDataTool::getInstance().getLevelProfile(databaseModule::eBattleLevelsTypes::FOREST_LEVEL);

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
//		auto battleDB = GET_DATABASE_MANAGER().getBattleLevelsDB();
//		battleDB.executeLoadData();
//		auto test = battleDB.

//		auto questsDB = GET_DATABASE_MANAGER().getQuestsDB();
//		questsDB.executeLoadData();

		return eTasksStatus::STATUS_OK;
	});

	return result;
}
