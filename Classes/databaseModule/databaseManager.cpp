#include "databaseManager.h"
#include "databases/tilesDB.h"

using namespace sr;
using namespace sr::databaseModule;

databaseManager *currentDBInstance = nullptr;

databaseManager::databaseManager() {
	tileDatabaseInstance = new tilesDB("properties/db/tilesDB.json");
}

databaseManager::~databaseManager() = default;

databaseManager &databaseManager::getInstance() {
	if (currentDBInstance == nullptr) {
		currentDBInstance = new databaseManager();
	}
	return *currentDBInstance;
}
