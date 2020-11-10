#ifndef SWIPE_RPG_DATABASEMANAGER_H
#define SWIPE_RPG_DATABASEMANAGER_H

#include "cocos2d.h"

#define GET_DATABASE_MANAGER() sr::databaseModule::databaseManager::getInstance()

namespace sr {
	namespace databaseModule {
		class tileDatabase;

		class databaseManager {
		public:
			databaseManager();
			~databaseManager();
			static databaseManager &getInstance();

			tileDatabase* getTileDatabase() { return tileDatabaseInstance; }

		private:
			tileDatabase* tileDatabaseInstance = nullptr;
		};
	}
}


#endif //SWIPE_RPG_DATABASEMANAGER_H
