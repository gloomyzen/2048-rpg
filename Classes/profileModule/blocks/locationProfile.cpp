#include "locationProfile.h"
#include "common/debugModule/logManager.h"
#include "cocos2d.h"

using namespace sr::profileModule;

locationProfile::locationProfile() {}

locationProfile::~locationProfile() {}

bool locationProfile::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &data) {
	//todo, wip load data
//	auto first = data.FindMember("forest");
	for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
		if (!it->name.IsString() || !it->value.IsObject()) {
			LOG_ERROR("locationProfile::load: not valid data from json.");
			continue;
		}
		auto name = databaseModule::levelTypesMap.find(it->name.GetString());
		auto loc = new sLocationLog();
		if (loc->load(it->name.GetObjectJ()) && name != databaseModule::levelTypesMap.end()) {
			location.insert({name->second, loc});
		}
	}

	return false;
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
		auto array = questLogIt->value.GetArray();
//		for todo
	}
	return false;
}
