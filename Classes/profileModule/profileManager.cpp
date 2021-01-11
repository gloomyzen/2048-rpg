#include "cocos2d.h"
#include "common/debugModule/logManager.h"
#include "profileManager.h"
#include "profileModule/blocks/locationProfile.h"

using namespace sr;
using namespace sr::profileModule;

profileManager *profileMgrInstance = nullptr;

profileManager::profileManager() {
	load();
}

profileManager::~profileManager() {
	save();
	profileBlocks.clear();
}

profileManager &profileManager::getInstance() {
	if (profileMgrInstance == nullptr) {
		profileMgrInstance = new profileManager();
	}
	return *profileMgrInstance;
}

void profileManager::load() {
	const std::string& path = "config/user_profile.json";
	const std::string& jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	rapidjson::Document data;
	data.Parse<0>(jsonStr.c_str());
	if (data.HasParseError() || data.IsNull()) {
		LOG_ERROR("profileManager::load: default profile json is not valid!");
	}

	auto profile = cocos2d::UserDefault::getInstance()->getStringForKey("profile", std::string());
	registerBlocks();
	loadProfile(data, profile);
}

void profileManager::save() {
	//
}

void profileManager::loadProfile(const rapidjson::Document &data, const std::string &profileJson) {
	if (!data.IsObject()) {
		LOG_ERROR("userDataTool::load: Object not found!");
	}

	for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
		//
	}
}

void profileManager::registerBlocks() {
	profileBlocks["location"] = [](){ return new locationProfile(); };
}
