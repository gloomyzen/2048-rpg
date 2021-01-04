#include "databaseManager.h"
#include "databases/tilesDB.h"
#include "databases/gameModesDB.h"
#include "databases/battleLevelsDB.h"

using namespace sr;
using namespace sr::databaseModule;

databaseManager *currentDBInstance = nullptr;

databaseManager::databaseManager() {
	tileDatabaseInstance = new tilesDB("properties/database/tiles/db.json");
	gameModesDatabaseInstance = new gameModesDB("properties/database/gameModes/db.json");
	battleLevelsDatabaseInstance = new battleLevelsDB("properties/database/battleLevels/db.json");
}

databaseManager::~databaseManager() = default;

databaseManager &databaseManager::getInstance() {
	if (currentDBInstance == nullptr) {
		currentDBInstance = new databaseManager();
	}
	return *currentDBInstance;
}
