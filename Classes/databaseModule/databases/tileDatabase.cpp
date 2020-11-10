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
	for (const auto& tileType : tileTypesMap) {
		//todo remove find element by key
		auto row = typesIter->value.FindMember(tileType.first.c_str());
		if (row == typesIter->value.MemberEnd() || !row->value.IsObject()) continue;
		//todo
		// 1 add struct for tileTypes - done
		// 2 parse json by struct - wip
		sTilesTypes item;
		item.type = tileType.second;
		auto armorIter = row->value.FindMember("armor");
		if (armorIter != row->value.MemberEnd() && armorIter->value.IsInt()) {
			item.armor = armorIter->value.GetInt();
		}
	}
}
