#include "userDataTool.h"
#include "cocos2d.h"

using namespace sr::databaseModule;

userDataTool *currentUserDataInstance = nullptr;

userDataTool::userDataTool(const std::string& path) {
	setPath(path);
}

userDataTool::~userDataTool() {}

void userDataTool::load(const rapidjson::Document&) {}

void userDataTool::executeLoadData() {}

userDataTool &userDataTool::getInstance() {
	if (currentUserDataInstance == nullptr) {
		currentUserDataInstance = new userDataTool("config/user_profile.json");
	}
	return *currentUserDataInstance;
}

sUserProfileStruct *userDataTool::getUserProfile() {
	if (isLoaded()) return userData;

	//todo need reformat class to module
	const std::string &jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile(getPath());
	rapidjson::Document data;
	data.Parse<0>(jsonStr.c_str());
	if (!isValidJson(data)) {
		LOG_ERROR("userDataTool::getUserProfile: default profile json is not valid!");
	} else {
		auto profile = cocos2d::UserDefault::getInstance()->getStringForKey("profile", std::string());
		loadProfile(data, profile);
	}

	return userData;
}

void userDataTool::loadProfile(const rapidjson::Document& data, const std::string& profileJson) {
	if (!data.IsObject()) {
		LOG_ERROR("userDataTool::load: Object not found!");
	}

	for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
		//
	}
}

