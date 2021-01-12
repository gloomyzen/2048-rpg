#ifndef SWIPE_RPG_LOCATIONPROFILE_H
#define SWIPE_RPG_LOCATIONPROFILE_H

#include "profileModule/profileBlockInterface.h"
#include "databaseModule/databases/gameEnums.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace sr {
	namespace profileModule {

		struct sQuestLog {
			unsigned int itemId = 0u;
			int count = 0;
		};

		struct sLocationLog {
			int id = 0;
			unsigned int questId = 0u;
			std::vector<sQuestLog*> questLog;

			bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &);
		};


		class locationProfile : public profileBlockInterface {
		public:
			locationProfile();
			~locationProfile() override;
			bool load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &) override;
			bool save(rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &) override;

			sLocationLog* getLogByLevel(databaseModule::eBattleLevelsTypes);
			std::map<databaseModule::eBattleLevelsTypes, sLocationLog*> getAllLog() { return location; }

		private:
			std::map<databaseModule::eBattleLevelsTypes, sLocationLog*> location;
		};

	}
}


#endif //SWIPE_RPG_LOCATIONPROFILE_H
