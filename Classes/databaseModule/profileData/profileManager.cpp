#include "profileManager.h"

using namespace sr;
using namespace sr::databaseModule;

profileManager *profileMgrInstance = nullptr;

profileManager::profileManager() {}

profileManager::~profileManager() {}

profileManager &profileManager::getInstance() {
	if (profileMgrInstance == nullptr) {
		profileMgrInstance = new profileManager();
	}
	return *profileMgrInstance;
}
