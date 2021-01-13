#include "locationProfile.h"
#include "common/debugModule/logManager.h"
#include "cocos2d.h"

using namespace sr::profileModule;

locationProfile::locationProfile() {}

locationProfile::~locationProfile() {}

bool locationProfile::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &data) {
	for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
		if (!it->name.IsString() || !it->value.IsArray()) {
			LOG_ERROR("locationProfile::load: not valid data from json.");
			continue;
		}
		auto name = databaseModule::levelTypesMap.find(it->name.GetString());
		std::vector<sLocationLog*> locList;
		auto locationArray = it->value.GetArray();
		for (auto item = locationArray.Begin(); item != locationArray.End(); ++item) {
			if (item->IsObject()) {
				auto loc = new sLocationLog();
				if (loc->load(item->GetObjectJ()) && name != databaseModule::levelTypesMap.end()) {
					locList.push_back(loc);
				}
			} else {
				LOG_ERROR(STRING_FORMAT("locationProfile::load: data by key '%s' is not object.", name->first.c_str()));
			}
		}
		location.insert({name->second, locList});
	}

	return true;
}

bool locationProfile::save(rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &) {
	return false;
}

std::vector<sLocationLog*>& locationProfile::getLogByLevel(databaseModule::eBattleLevelsTypes type) {
	auto fnd = location.find(type);
	if (fnd != location.end()) return fnd->second;

	LOG_ERROR(STRING_FORMAT("locationProfile::getLogByLevel: can't find location by type '%d'.", static_cast<int>(type)));
	std::vector<sLocationLog*> levelLoc;
	location.insert({type, levelLoc});
	return location[type];
}

bool sLocationLog::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& data) {
	auto idIt = data.FindMember("id");
	auto questIdIt = data.FindMember("quest");
	auto questLogIt = data.FindMember("questProgress");
	if (idIt->value.IsInt() && questIdIt->value.IsUint() && questLogIt->value.IsArray()) {
		id = idIt->value.GetInt();
		questId = questIdIt->value.GetUint();
		auto _array = questLogIt->value.GetArray();
		for (auto it = _array.Begin(); it != _array.End(); ++it) {
			if (it->IsObject()) {
				auto _id = it->FindMember("id");
				auto _count = it->FindMember("count");
				if (_id->value.IsUint() && _count->value.IsInt()) {
					auto item = new sQuestLog();
					item->itemId = _id->value.GetUint();
					item->count = _count->value.GetInt();
					questLog.push_back(item);
				}
			}
		}
		return true;
	}
	return false;
}
