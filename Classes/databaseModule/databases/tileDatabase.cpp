#include "tileDatabase.h"
#include "cocos2d.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <map>

using namespace sr::databaseModule;

static std::map<std::string, eTileTypes> tileTypesMap = {
		{"none", eTileTypes::NONE},
		{"hero", eTileTypes::HERO},
		{"item", eTileTypes::ITEM},
		{"enemy", eTileTypes::ENEMY}
};

tileDatabase::tileDatabase(const std::string& path) {
	const std::string &regionStr = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
	rapidjson::Document data;
	data.Parse<0>(regionStr.c_str());
	if (isValidJson(data)) {
		load(data);
	}
}

tileDatabase::~tileDatabase() {}

void tileDatabase::load(const rapidjson::Document& data) {
	const auto typesIter = data.FindMember("types");
	if (typesIter == data.MemberEnd() || !typesIter->value.IsObject()) {
		//todo log warning
		return;
	}
	for (auto iter = typesIter->value.MemberBegin(); iter != typesIter->value.MemberEnd(); ++iter) {
		sTilesTypes item;
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
		///Armor
		auto armorIter = iter->value.FindMember("armor");
		if (armorIter != iter->value.MemberEnd() && armorIter->value.IsInt()) {
			item.armor = armorIter->value.GetInt();
		}
		///isCollect
		auto collectIter = iter->value.FindMember("isCollect");
		if (collectIter != iter->value.MemberEnd() && collectIter->value.IsBool()) {
			item.isCollect = collectIter->value.GetBool();
		}
		///isHero
		auto heroIter = iter->value.FindMember("isHero");
		if (heroIter != iter->value.MemberEnd() && heroIter->value.IsBool()) {
			item.isHero = heroIter->value.GetBool();
		}
		///isEnemy
		auto enemyIter = iter->value.FindMember("isEnemy");
		if (enemyIter != iter->value.MemberEnd() && enemyIter->value.IsBool()) {
			item.isEnemy = enemyIter->value.GetBool();
		}
		//todo
		// 1 add parse other params
		// 2 parse upgrade
	}
}
