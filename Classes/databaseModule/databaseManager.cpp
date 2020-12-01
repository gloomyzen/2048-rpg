#include "databaseManager.h"
#include "databases/tileDatabase.h"

using namespace sr;
using namespace sr::databaseModule;

databaseManager *currentDBInstance = nullptr;

databaseManager::databaseManager() {
	tileDatabaseInstance = new tileDatabase("properties/db/tilesDB.json");
}

databaseManager::~databaseManager() = default;

databaseManager &databaseManager::getInstance() {
	if (currentDBInstance == nullptr) {
		currentDBInstance = new databaseManager();
	}
	return *currentDBInstance;
}
