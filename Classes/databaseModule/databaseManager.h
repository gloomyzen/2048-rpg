#ifndef SWIPE_RPG_DATABASEMANAGER_H
#define SWIPE_RPG_DATABASEMANAGER_H

#include "cocos2d.h"

#define GET_DATABASE_MANAGER() sr::databaseModule::databaseManager::getInstance()

namespace sr {
	namespace databaseModule {

		class databaseManager {
		public:
			databaseManager();
			~databaseManager();
			static databaseManager &getInstance();
		};
	}
}


#endif //SWIPE_RPG_DATABASEMANAGER_H
