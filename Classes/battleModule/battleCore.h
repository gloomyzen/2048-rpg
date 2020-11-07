#ifndef SWIPE_RPG_BATTLECORE_H
#define SWIPE_RPG_BATTLECORE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "boardNode.h"

namespace sr {
	namespace battleModule {
	using namespace cocos2d;
	using namespace common;

		class battleCore : public coreModule::nodeProperties, public Node {
		public:
			battleCore();
			~battleCore() = default;
			CREATE_FUNC(battleCore);

		private:
			boardNode* board = nullptr;
			ClippingNode* clippingNode = nullptr;
		};
	}
}


#endif //SWIPE_RPG_BATTLECORE_H
