#include "cocostudio/SimpleAudioEngine.h"
#include "scrollHolder.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/battleLevelsDB.h"
#include "databaseModule/databases/questsDB.h"
#include "profileModule/profileManager.h"
#include "databaseModule/block/userDataTool.h"
#include "common/debugModule/logManager.h"

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
//		auto questsDB = GET_DATABASE_MANAGER().getQuestsDB();
//		questsDB.executeLoadData();

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
			auto node = new nodeProperties<Node>();
			node->setName(STRING_FORMAT("mapPiece_%d_row%d", currentPiece->id, currentPiece->row));
			node->setPosition(currentPiece->position);
			node->loadProperty(currentPiece->property);
			scrollView->addChild(node);
			piecesList.push_back(new sMapPiece(currentPiece, *it, node));
		}
		return eTasksStatus::STATUS_OK;
	});

	return result;
}
