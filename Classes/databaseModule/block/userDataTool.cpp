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
	if (!data.IsObject()) {
		LOG_ERROR("userDataTool::load: Object not found!");
	}

	for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
		//
	}
}

sUserProfileStruct *userDataTool::getUserProfile() {
	if (isLoaded()) return userData;

	auto profile = cocos2d::UserDefault::getInstance()->getStringForKey("profile", "");
	if (!profile.empty()) {
		//todo load local profile
	} else {
		//todo load new profile
	}
	return nullptr;
}

