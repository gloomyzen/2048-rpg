#include "tilesDB.h"
#include "cocos2d.h"
#include "common/debugModule/logManager.h"
#include <map>

using namespace sr::databaseModule;

std::map<std::string, eTileTypes> tileTypesMap = {
		{"env", eTileTypes::ENVIRONMENT},
		{"hero", eTileTypes::HERO},
		{"item", eTileTypes::ITEM},
		{"enemy", eTileTypes::ENEMY}
};

tilesDB::tilesDB(const std::string& path) {
	setPath(path);
}

tilesDB::~tilesDB() = default;

void tilesDB::load(const rapidjson::Document& data) {
	//types to method
	const auto typesIter = data.FindMember("types");
	if (typesIter == data.MemberEnd() || !typesIter->value.IsObject()) {
		LOG_ERROR("tileDatabase::load: Object 'type' is not valid!");
	}
	for (auto iter = typesIter->value.MemberBegin(); iter != typesIter->value.MemberEnd(); ++iter) {
		sTileData item;
		item.name = iter->name.GetString();
		///Type
		auto typeIter = iter->value.FindMember("type");
		if (typeIter != iter->value.MemberEnd() && typeIter->value.IsString()) {
			auto type = typeIter->value.GetString();
			auto it = tileTypesMap.find(type);
			if (it != tileTypesMap.end()) {
				item.type = it->second;
			}
		}
		///Attack
		auto attackIter = iter->value.FindMember("attack");
		if (attackIter != iter->value.MemberEnd() && attackIter->value.IsInt()) {
			item.attack = attackIter->value.GetInt();
		}
		///Hp
		auto hpIter = iter->value.FindMember("hp");
		if (hpIter != iter->value.MemberEnd() && hpIter->value.IsInt()) {
			item.hp = hpIter->value.GetInt();
		}

		///Upgrade
		auto upgIter = iter->value.FindMember("upgrade");
		if (upgIter != iter->value.MemberEnd() && upgIter->value.IsArray()) {
			for (auto upgradeIt = upgIter->value.Begin(); upgradeIt != upgIter->value.End(); ++upgradeIt) {
				auto upg = sTilesUpgrade(upgradeIt->GetObjectJ());
				if (upg.isValid()) {
					item.tileUpgrade.insert({upg.id, upg});
				}
			}
		}
		tileList.insert({item.name, item});
	}
}

sTileData tilesDB::getTileByName(const std::string &name) {
	auto it = tileList.find(name);
	if (it != tileList.end()) {
		return it->second;
	}
	return sTileData();
}

bool tilesDB::tileExist(const std::string &name) {
	auto it = tileList.find(name);
	return it != tileList.end();
}

sTilesUpgrade::sTilesUpgrade(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& object) {
	///id
	auto idIter = object.FindMember("id");
	if (idIter != object.MemberEnd() && idIter->value.IsInt()) {
		id = idIter->value.GetInt();
	} else {
		LOG_ERROR("sTilesUpgrade::sTilesUpgrade: Object 'id' is not valid!");
	}
	///bg
	auto bgIter = object.FindMember("bg");
	if (bgIter != object.MemberEnd() && bgIter->value.IsString()) {
		bg = bgIter->value.GetString();
	} else {
		LOG_ERROR("sTilesUpgrade::sTilesUpgrade: Object 'bg' is not valid!");
	}
	///icon
	auto iconIter = object.FindMember("icon");
	if (iconIter != object.MemberEnd() && iconIter->value.IsString()) {
		icon = iconIter->value.GetString();
	} else {
		LOG_ERROR("sTilesUpgrade::sTilesUpgrade: Object 'icon' is not valid!");
	}
}
