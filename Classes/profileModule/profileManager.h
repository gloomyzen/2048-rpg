#ifndef SWIPE_RPG_PROFILEMANAGER_H
#define SWIPE_RPG_PROFILEMANAGER_H

#include "profileModule/profileBlockInterface.h"
#include <map>
#include <string>
#include <functional>

namespace sr {
	namespace profileModule {

		class profileManager {
		public:
			static profileManager &getInstance();
		private:
			profileManager();
			~profileManager();

			void load();
			void save();
			void loadProfile(const rapidjson::Document& data, const std::string& profileJson);
			void registerBlocks();

			std::map<std::string, std::function<profileBlockInterface*()>> profileBlocks;
		};
	}
}


#endif //SWIPE_RPG_PROFILEMANAGER_H
