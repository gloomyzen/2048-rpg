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
	registerBlocks();
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

	loadProfile(defaultProfile, localProfile);
}

void profileManager::save() {
	//todo
}

void profileManager::loadProfile(const rapidjson::Document &defaultData, const rapidjson::Document &localData) {
	if (!defaultData.IsObject() || defaultData.HasParseError() || defaultData.IsNull()) {
		LOG_ERROR("profileManager::loadProfile: Object not found! Profile not loaded!");
		return;
	}
	auto localProfileValid = !localData.HasParseError() && !localData.IsNull() && localData.IsObject();

	for (auto it = defaultData.MemberBegin(); it != defaultData.MemberEnd(); ++it) {
		if (it->name.IsString() && it->value.IsObject()) {
			auto key = it->name.GetString();
			auto blockIt = profileBlocks.find(key);
			auto findBlock = blockIt != profileBlocks.end();

			if (localProfileValid && findBlock) {
				auto localIt = localData.FindMember(key);
				if (localIt != localData.MemberEnd()) {
					blockIt->second()->load(localIt->value.GetObjectJ());
					continue;
				}
			}
			blockIt->second()->load(it->value.GetObjectJ());

		}
	}


}

void profileManager::registerBlocks() {
	profileBlocks["location"] = [](){ return new locationProfile(); };
}
