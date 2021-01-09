#ifndef SWIPE_RPG_USERDATATOOL_H
#define SWIPE_RPG_USERDATATOOL_H

#include "databaseModule/databases/gameEnums.h"
#include <map>
#include <string>
#include <vector>

namespace sr {
	namespace databaseModule {

		struct sUserProfileQuestProgress {
			unsigned int itemId;
			int count;
		};

		struct sUserProfileLocationProgress {
			int id;
			unsigned int questId;
			std::vector<sUserProfileQuestProgress*> questProgress;
		};

		struct sUserProfileStruct {
			std::map<eBattleLevelsTypes, sUserProfileLocationProgress*> location;
		};

		class userDataTool {
		public:
			userDataTool();
			~userDataTool();

		};
	}
}


#endif //SWIPE_RPG_USERDATATOOL_H
