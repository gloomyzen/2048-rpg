#include "userDataTool.h"
#include "cocos2d.h"

using namespace sr::databaseModule;

userDataTool *currentUserDataInstance = nullptr;

userDataTool::userDataTool(const std::string& path) {
	setPath(path);
}

userDataTool::~userDataTool() {}

userDataTool &userDataTool::getInstance() {
	if (currentUserDataInstance == nullptr) {
		currentUserDataInstance = new userDataTool("config/user_profile.json");
	}
	return *currentUserDataInstance;
}

void userDataTool::load(const rapidjson::Document& data) {
	//
}

