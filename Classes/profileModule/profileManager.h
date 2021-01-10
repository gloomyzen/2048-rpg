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
			profileManager();
			~profileManager();
			static profileManager &getInstance();

		private:
			std::map<std::string, std::function<void()>> profileBlocks;
		};
	}
}


#endif //SWIPE_RPG_PROFILEMANAGER_H
