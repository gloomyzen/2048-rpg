#include "battleLevelsDB.h"
#include "common/coreModule/resources/resourceManager.h"

using namespace sr::databaseModule;

std::map<std::string, eBattleLevelsTypes> levelTypesMap = {
		{"forest",	eBattleLevelsTypes::FOREST_LEVEL},
		{"cave",	eBattleLevelsTypes::CAVE_LEVEL},
		{"crystal",	eBattleLevelsTypes::CRYSTAL_LEVEL},
		{"lava",	eBattleLevelsTypes::LAVA_LEVEL},
};

battleLevelsDB::battleLevelsDB(const std::string &path) {
	setPath(path);
}

battleLevelsDB::~battleLevelsDB() = default;

void battleLevelsDB::load(const rapidjson::Document &data) {
	if (!data.IsObject()) {
		LOG_ERROR("battleLevelsDB::load: Object not found!");
	}
	for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
		std::string locationName = it->name.GetString();
		std::string propertyPath = it->value.GetString();

		if (!propertyPath.empty() && cocos2d::FileUtils::getInstance()->isFileExist(propertyPath)) {
			auto item = new sLevelData();
			if (item->load(propertyPath)
			&& levelTypesMap.find(locationName) != levelTypesMap.end()) {
				levelsMap.insert({levelTypesMap.find(locationName)->second, item});
			}
		} else {
			LOG_ERROR(cocos2d::StringUtils::format("battleLevelsDB::load: Level %d has invalid property path.", std::stoi(id)));
		}
	}
}

bool sLevelData::load(const std::string& path) {
	auto json = GET_JSON(path);
	if (json.HasParseError() || !json.IsObject()) {
		LOG_ERROR("nodeProperties::loadProperty Json file '" + path + "' has erroes or not found!");
		return false;
	}
	//wip this
	return false;
}
