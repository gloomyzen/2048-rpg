#ifndef SWIPE_RPG_USERDATATOOL_H
#define SWIPE_RPG_USERDATATOOL_H

#include "databaseModule/databases/gameEnums.h"
#include "profileModule/profileManager.h"
#include "profileModule/blocks/locationProfile.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <map>
#include <string>
#include <vector>

namespace sr {
	namespace databaseModule {

		class userDataTool {
		public:
			userDataTool();
			~userDataTool();
			static userDataTool &getInstance();
			profileModule::sLocationLog* getLevelProfile(databaseModule::eBattleLevelsTypes);

		};
	}
}


#endif //SWIPE_RPG_USERDATATOOL_H
