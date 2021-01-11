#ifndef SWIPE_RPG_PROFILEMANAGER_H
#define SWIPE_RPG_PROFILEMANAGER_H

#include "profileModule/profileBlockInterface.h"
#include <map>
#include <string>
#include <functional>

#define GET_PROFILE() sr::profileModule::profileManager::getInstance()

namespace sr {
	namespace profileModule {
		class locationProfile;

		class profileManager {
		public:
			profileManager();
			~profileManager();
			static profileManager &getInstance();

			locationProfile* getLocationBlock() { return locationBlock; }
		private:

			void load();
			void save();
			void loadProfile(const rapidjson::Document& defaultData, const rapidjson::Document& localData);
			void registerBlocks();

			std::map<std::string, std::function<profileBlockInterface*()>> profileBlocks;

			locationProfile* locationBlock = nullptr;
		};
	}
}


#endif //SWIPE_RPG_PROFILEMANAGER_H
