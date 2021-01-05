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

		if (!propertyPath.empty()) {
			auto item = new sLevelData();
			if (item->load(propertyPath)
			&& levelTypesMap.find(locationName) != levelTypesMap.end()) {
				levelsMap.insert({levelTypesMap.find(locationName)->second, item});
			}
		} else {
			LOG_ERROR(cocos2d::StringUtils::format("battleLevelsDB::load: Level '%s' has invalid property path.", locationName.c_str()));
		}
	}
}

bool sLevelData::load(const std::string& path) {
	auto json = GET_JSON(path);
	if (json.HasParseError() || !json.IsObject()) {
		LOG_ERROR("nodeProperties::loadProperty Json file '" + path + "' has erroes or not found!");
		return false;
	}
	std::map<std::string, std::string> typePath;
	auto typesIt = json.FindMember("types");
	if (typesIt != json.MemberEnd() && typesIt->value.IsArray()) {
		for (auto type = typesIt->value.Begin(); type != typesIt->value.End(); ++type) {
			auto name = type->FindMember("name");
			auto property = type->FindMember("property");
			if (name->value.IsString() && property->value.IsString()) {
				//wip this
			}
		}
		//todo parse
	}
	//wip this
	return false;
}
