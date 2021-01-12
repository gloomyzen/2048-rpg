#include "locationProfile.h"
#include "common/debugModule/logManager.h"
#include "cocos2d.h"

using namespace sr::profileModule;

locationProfile::locationProfile() {}

locationProfile::~locationProfile() {}

bool locationProfile::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &data) {
	for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
		if (!it->name.IsString() || !it->value.IsObject()) {
			LOG_ERROR("locationProfile::load: not valid data from json.");
			continue;
		}
		auto name = databaseModule::levelTypesMap.find(it->name.GetString());
		auto loc = new sLocationLog();
		if (loc->load(it->value.GetObjectJ()) && name != databaseModule::levelTypesMap.end()) {
			location.insert({name->second, loc});
		}
	}

	return true;
}

bool locationProfile::save(rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &) {
	return false;
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
