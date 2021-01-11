#ifndef SWIPE_RPG_PROFILEMANAGER_H
#define SWIPE_RPG_PROFILEMANAGER_H

#include "profileModule/profileBlockInterface.h"
#include <map>
#include <string>
#include <functional>

#define GET_PROFILE() sr::profileModule::profileManager::getInstance()

namespace sr {
	namespace profileModule {

		class profileManager {
		public:
			profileManager();
			~profileManager();
			static profileManager &getInstance();
		private:

			void load();
			void save();
			void loadProfile(const rapidjson::Document& defaultData, const rapidjson::Document& localData);
			void registerBlocks();

			std::map<std::string, std::function<profileBlockInterface*()>> profileBlocks;
		};
	}
}


#endif //SWIPE_RPG_PROFILEMANAGER_H
