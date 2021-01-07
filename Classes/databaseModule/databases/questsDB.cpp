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
			//wip error, one condition have array of objects, not object
			if (condition != it->value.MemberEnd()) {
				for (auto conditionIt = condition->value.MemberBegin(); conditionIt != condition->value.MemberEnd(); ++conditionIt) {
					if (!conditionIt->name.IsString() || !conditionIt->value.IsObject()) {
						LOG_ERROR(STRING_FORMAT("questsDB::load: Quest '%s' has invalid condition.", id.c_str()));
						continue;
					}
					auto questType = questTypeList.find(static_cast<std::string>(conditionIt->name.GetString()));
					if (questType == questTypeList.end()) {
						LOG_ERROR(STRING_FORMAT("questsDB::load: Quest '%s' has invalid type '%s'.", id.c_str(), conditionIt->name.GetString()));
						continue;
					}
//						questType->second
				}
			}
		}
	}
}
