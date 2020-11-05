#ifndef SWIPE_RPG_BATTLECORE_H
#define SWIPE_RPG_BATTLECORE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace battleModule {
	using namespace cocos2d;
	using namespace common;

		class battleCore : public Node {
		public:
			battleCore();
			~battleCore() = default;
			CREATE_FUNC(battleCore);
			static Node *createNode() { return battleCore::create(); }
			bool init() override {
				if (!Node::init()) {
					return false;
				}
				return true;
			}

		private:
		};
	}
}


#endif //SWIPE_RPG_BATTLECORE_H
