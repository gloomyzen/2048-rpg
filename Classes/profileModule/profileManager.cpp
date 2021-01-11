#include "cocos2d.h"
#include "common/debugModule/logManager.h"
#include "profileManager.h"
#include "profileModule/blocks/locationProfile.h"
#include "common/coreModule/resources/resourceManager.h"
#include "common/coreModule/resources/loaders/jsonLoader.h"

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
	const std::string& path = "config/user_profile";
	auto defaultProfile = GET_JSON_MANAGER()->loadJson(path);
	auto profile = cocos2d::UserDefault::getInstance()->getStringForKey("profile", std::string());
	auto localProfile = GET_JSON_MANAGER()->stringToJson(profile);

	registerBlocks();
	loadProfile(defaultProfile, localProfile);
}

void profileManager::save() {
	//
}

void profileManager::loadProfile(const rapidjson::Document &defaultData, const rapidjson::Document &localData) {
	if (!defaultData.IsObject() || defaultData.HasParseError() || defaultData.IsNull()) {
		LOG_ERROR("profileManager::loadProfile: Object not found! Profile not loaded!");
		return;
	}

	for (auto it = defaultData.MemberBegin(); it != defaultData.MemberEnd(); ++it) {
		//
	}
}

void profileManager::registerBlocks() {
	profileBlocks["location"] = [](){ return new locationProfile(); };
}
