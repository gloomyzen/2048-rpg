#ifndef SWIPE_RPG_DATABASEMANAGER_H
#define SWIPE_RPG_DATABASEMANAGER_H

#include "cocos2d.h"

#define GET_DATABASE_MANAGER() sr::databaseModule::databaseManager::getInstance()

namespace sr {
	namespace databaseModule {
		class tilesDB;

		class databaseManager {
		public:
			databaseManager();
			~databaseManager();
			static databaseManager &getInstance();

			tilesDB* getTileDatabase() { return tileDatabaseInstance; }

		private:
			tilesDB* tileDatabaseInstance = nullptr;
		};
	}
}


#endif //SWIPE_RPG_DATABASEMANAGER_H
