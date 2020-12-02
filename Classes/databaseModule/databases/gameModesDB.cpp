#include "gameModesDB.h"
#include "cocos2d.h"

using namespace sr;
using namespace sr::databaseModule;

static std::map<std::string, eGameMode> gmTypesMap = {
		{"endless", eGameMode::ENDLESS},
};

gameModesDB::gameModesDB(const std::string &path) {
	const std::string &regionStr = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	rapidjson::Document data;
	data.Parse<0>(regionStr.c_str());
	if (isValidJson(data)) {
		load(data);
	}
}

gameModesDB::~gameModesDB() = default;

void gameModesDB::load(const rapidjson::Document &data) {
	auto test = data.GetArray();
	if (!data.IsArray()) {
		LOG_ERROR("gameModesDB::load: Array not found!!");
	}
	for (auto it = data.Begin(); it != data.End(); ++it) {
		if (!it->IsObject()) {
			LOG_ERROR("gameModesDB::load: Next data is not object!!!");
		}
		auto item = new sGameModeData();

		auto name = it->FindMember("name");
		if (name != it->MemberEnd() && name->value.IsString()) {
			item->name = name->value.GetString();
		}

		auto type = it->FindMember("type");
		if (type != it->MemberEnd() && type->value.IsString()) {
			auto currentType = gmTypesMap.find(name->value.GetString());
			if (currentType != gmTypesMap.end()) {
				item->type = currentType->second;
			} else {
				LOG_ERROR(cocos2d::StringUtils::format("gameModesDB::load: Try get unregistered type %s", name->value.GetString()));
			}
		}
	}

}
