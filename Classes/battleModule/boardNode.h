#ifndef SWIPE_RPG_BOARDNODE_H
#define SWIPE_RPG_BOARDNODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "battleModule/tiles/tileNode.h"
#include <vector>

namespace sr {
	namespace battleModule {
		using namespace cocos2d;
		using namespace common;

		struct sTileData {
			cocos2d::Vec2 pos;
			tileNode* tile;
		};

		class boardNode : public coreModule::nodeProperties, public Sprite {
		public:
			boardNode();
			~boardNode();
			CREATE_FUNC(boardNode);

		private:
			void initBoard();
			std::vector<sTileData> tileList;
		};
	}
}

#endif //SWIPE_RPG_BOARDNODE_H