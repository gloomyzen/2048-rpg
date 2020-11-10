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

void tileDatabase::load(const rapidjson::Document&) {
	//1 check errors
}
