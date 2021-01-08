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
			LOG_ERROR(STRING_FORMAT("battleLevelsDB::load: Level '%s' has invalid property path.", locationName.c_str()));
		}
	}
}

bool sLevelData::load(const std::string& path) {
	auto json = GET_JSON(path);
	if (json.HasParseError() || !json.IsObject()) {
		LOG_ERROR(STRING_FORMAT("sLevelData::load Json file '%s' contains errors or not found!", path.c_str()));
		return false;
	}
	auto locNameIt = json.FindMember("name");
	if (locNameIt != json.MemberEnd()) {
		this->locationName = locNameIt->value.GetString();
	} else {
		LOG_ERROR(STRING_FORMAT("sLevelData::load Json file '%s' does not have property 'name'.", path.c_str()));
	}
	std::map<std::string, std::string> typePath;
	auto typesIt = json.FindMember("types");
	if (typesIt != json.MemberEnd() && typesIt->value.IsArray()) {
		for (auto type = typesIt->value.Begin(); type != typesIt->value.End(); ++type) {
			auto name = type->FindMember("name");
			auto prop = type->FindMember("property");
			if (name->value.IsString() && prop->value.IsString()) {
				typePath.insert({name->value.GetString(), prop->value.GetString()});
			}
		}
	}

	auto mapIt = json.FindMember("map");
	if (mapIt != json.MemberEnd() && mapIt->value.IsArray()) {
		for (auto row = mapIt->value.Begin(); row != mapIt->value.End(); ++row) {
			auto x = row->FindMember("x");
			auto y = row->FindMember("y");
			auto type = row->FindMember("type");
			if (x->value.IsInt() && y->value.IsInt() && type->value.IsString()) {
				auto prop = typePath.find(type->value.GetString());
				if (prop != typePath.end()) {
					currentMap.insert({cocos2d::Vec2(x->value.GetFloat(), y->value.GetFloat()), prop->second});
				}
			}
		}
	}

	return true;
}
