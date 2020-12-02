#include "gameModesDB.h"
#include "cocos2d.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/tilesDB.h"

using namespace sr;
using namespace sr::databaseModule;

std::map<std::string, eGameMode> gmTypesMap = {
		{"endless", eGameMode::ENDLESS},
};

gameModesDB::gameModesDB(const std::string &path) {
	setPath(path);
}

gameModesDB::~gameModesDB() = default;

void gameModesDB::load(const rapidjson::Document &data) {
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
		} else {
			LOG_ERROR("gameModesDB::load: Attribute name is not found!");
		}

		auto type = it->FindMember("type");
		if (type != it->MemberEnd() && type->value.IsString()) {
			auto currentType = gmTypesMap.find(type->value.GetString());
			if (currentType != gmTypesMap.end()) {
				item->type = currentType->second;
			} else {
				LOG_ERROR(cocos2d::StringUtils::format("gameModesDB::load: Try get unregistered type %s", type->value.GetString()));
			}
		} else {
			LOG_ERROR("gameModesDB::load: Attribute type is not found!");
		}

		auto heroTile = it->FindMember("heroTile");
		if (heroTile != it->MemberEnd() && heroTile->value.IsString()) {
			auto tileDb = GET_DATABASE_MANAGER().getTileDatabase();
			tileDb.executeLoadData();
			if (tileDb.tileExist(heroTile->value.GetString())) {
				item->heroTile = tileDb.getTileByName(heroTile->value.GetString());
			} else {
				LOG_ERROR(cocos2d::StringUtils::format("gameModesDB::load: Tile by name %s not found!", heroTile->value.GetString()));
			}
		} else {
			LOG_ERROR("gameModesDB::load: Attribute heroTile is not found!");
		}


	}

}
