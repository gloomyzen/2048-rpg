#ifndef SWIPE_RPG_QUESTSDB_H
#define SWIPE_RPG_QUESTSDB_H

#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include "gameEnums.h"
#include <map>
#include <string>

namespace sr {
	namespace databaseModule {

		struct questItem {
			std::map<eQuestEntities, std::pair<unsigned int, int>> objectives;
		};

		class questsDB : public databaseInterface {
		public:
			explicit questsDB(const std::string&);
			~questsDB();
			void load(const rapidjson::Document&) override;

			std::map<unsigned int, questItem*> getAllQuest() { return questList; }
			questItem* getQuestById(unsigned int);

		private:
			std::map<unsigned int, questItem*> questList;
		};
	}
}

#endif //SWIPE_RPG_QUESTSDB_H
