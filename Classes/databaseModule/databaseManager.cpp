#include "databaseManager.h"

using namespace sr;
using namespace sr::databaseModule;

databaseManager *currentDBInstance = nullptr;

databaseManager::databaseManager() {};

databaseManager::~databaseManager() = default;

databaseManager &databaseManager::getInstance() {
	if (currentDBInstance == nullptr) {
		currentDBInstance = new databaseManager();
	}
	return *currentDBInstance;
}
