#ifndef SWIPE_RPG_BOARDNODE_H
#define SWIPE_RPG_BOARDNODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "battleModule/tiles/tileNode.h"
#include <vector>

#define BOARD_START_POS_X 0
#define BOARD_START_POS_Y 0
#define BOARD_COUNT_X 5
#define BOARD_COUNT_Y 5
#define BOARD_TOUCH_FORCE 75

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
			void clearTiles();
			void setDefaultPosition();
			void initHandling();
			void touchUpdate(Touch*, Event*);

			std::vector<std::vector<sTileData>> tileList;;
			Touch* lastTouchInfo = nullptr;
			bool isTouch = false;
		};
	}
}

#endif //SWIPE_RPG_BOARDNODE_H