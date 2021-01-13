#include "questsDB.h"

using namespace sr::databaseModule;

questsDB::questsDB(const std::string &path) {
	setPath(path);
}

questsDB::~questsDB() = default;

void questsDB::load(const rapidjson::Document &data) {
	if (!data.IsObject()) {
		LOG_ERROR("questsDB::load: Object not found!");
	}

	for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
		if (!it->name.IsString()) {
			LOG_ERROR("questsDB::load: Quest has invalid key.");
			continue;
		}
		std::string id = it->name.GetString();
		if (it->value.IsObject()) {
			auto condition = it->value.FindMember("condition");
			if (condition != it->value.MemberEnd()) {
				for (auto conditionIt = condition->value.MemberBegin(); conditionIt != condition->value.MemberEnd(); ++conditionIt) {
					if (!conditionIt->name.IsString() || !conditionIt->value.IsArray()) {
						LOG_ERROR(STRING_FORMAT("questsDB::load: Quest '%s' has invalid condition.", id.c_str()));
						continue;
					}
					auto questType = questTypeList.find(static_cast<std::string>(conditionIt->name.GetString()));
					if (questType == questTypeList.end()) {
						LOG_ERROR(STRING_FORMAT("questsDB::load: Quest '%s' has invalid type '%s'.", id.c_str(), conditionIt->name.GetString()));
						continue;
					}
					auto item = new questItem();
					for (auto object = conditionIt->value.GetArray().Begin(); object != conditionIt->value.GetArray().End(); ++object) {
						auto questID = object->GetObjectJ().FindMember("id");
						auto questCount = object->GetObjectJ().FindMember("count");
						if (questID != object->GetObjectJ().MemberEnd() && questCount != object->GetObjectJ().MemberEnd()
							&& questID->value.IsUint()
							&& questCount->value.IsInt()) {
							item->objectives.insert({questType->second, {questID->value.GetUint(), questCount->value.GetInt()}});
						} else {
							LOG_ERROR(STRING_FORMAT("questsDB::load: Quest '%s' has invalid properties in object '%s'.", id.c_str(), conditionIt->name.GetString()));
						}
					}
					if (!item->objectives.empty())
						questList.insert({static_cast<unsigned int>(std::stoi(id)), item});
				}
			}
		}
	}
}

questItem *questsDB::getQuestById(unsigned int id) {
	auto fnd = questList.find(id);
	if (fnd != questList.end()) return fnd->second;
	return nullptr;
}
