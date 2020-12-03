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

		auto spawnPerSwipe = it->FindMember("spawnPerSwipe");
		if (spawnPerSwipe != it->MemberEnd() && spawnPerSwipe->value.IsArray()) {
			item->loadSpawnData(spawnPerSwipe->value.GetArray());
		}

		auto tilesData = it->FindMember("tiles");
		if (tilesData != it->MemberEnd() && tilesData->value.IsArray()) {
			item->loadTileData(tilesData->value.GetArray());
		}

	}

}

sGameModeData *gameModesDB::getModeByType(eGameMode mode) {
	auto res = modesList.find(mode);
	if (res != modesList.end()) {
		return res->second;
	}
	return nullptr;
}

void sGameModeData::loadSpawnData(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstArray &array) {
	for (auto it = array.Begin(); it != array.End(); ++it) {
		auto count = it->FindMember("count");
		auto chance = it->FindMember("chance");
		if (count != it->MemberEnd() && chance != it->MemberEnd()) {
			auto item = new sSpawnChance(count->value.GetInt(), chance->value.GetInt());
			spawnPerSwipe.push_back(item);
		}
	}
}

void sGameModeData::loadTileData(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstArray &array) {
	auto tileDb = GET_DATABASE_MANAGER().getTileDatabase();
	tileDb.executeLoadData();
	for (auto it = array.Begin(); it != array.End(); ++it) {
		auto tileIt = it->FindMember("tile");
		auto chance = it->FindMember("chance");
		if (tileIt != it->MemberEnd() && chance != it->MemberEnd()) {
			if (!tileDb.tileExist(tileIt->value.GetString()))
				continue;

			auto tile = tileDb.getTileByName(tileIt->value.GetString());
			auto item = new sSpawnTile(tile, chance->value.GetInt());
			tiles.push_back(item);
		}
	}
}
