#ifndef SWIPE_RPG_TILENODE_H
#define SWIPE_RPG_TILENODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace battleModule {
		using namespace cocos2d;
		using namespace common;

		class tileNode : public coreModule::nodeProperties, public Sprite {
		public:
			tileNode();
			~tileNode() = default;
			CREATE_FUNC(tileNode);

		private:
		};
	}
}

#endif //SWIPE_RPG_TILENODE_H