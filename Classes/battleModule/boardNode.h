#ifndef SWIPE_RPG_BOARDNODE_H
#define SWIPE_RPG_BOARDNODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "battleModule/tiles/tileNode.h"
#include <utility>
#include <vector>
#include <functional>

#define BOARD_START_POS_X 0
#define BOARD_START_POS_Y 0
#define BOARD_COUNT_X 5
#define BOARD_COUNT_Y 5
#define BOARD_HERO_POS_X 2
#define BOARD_HERO_POS_Y 2
#define BOARD_TOUCH_FORCE 75

namespace sr {
	namespace battleModule {
		using namespace cocos2d;
		using namespace common;

		struct sTileNode {
			cocos2d::Vec2 pos;
			tileNode* tile;
		};

		enum class eSwipeDirection {
			UNDEFINED = 0,
			UP = 1,
			DOWN,
			LEFT,
			RIGHT
		};

		class boardNode : public coreModule::nodeProperties, public Sprite, public taskHolder {
		public:
			boardNode();
			~boardNode();
			CREATE_FUNC(boardNode);
			std::deque<nodeTasks> getTasks() override;

			void setHeroTileData(sTileData* heroTile);
			void initBoard();
			void setSwipeCallback(std::function<bool(eSwipeDirection)> clb) { swipeClb = std::move(clb); }

		private:
			void clearTiles();
			void setDefaultPosition();
			void initHandling();
			void touchUpdate(Touch*, Event*);

			std::vector<std::vector<sTileNode*>> tileList;
			sTileData* hero = nullptr;
			Touch* lastTouchInfo = nullptr;
			bool isTouch = false;
			std::function<bool(eSwipeDirection)> swipeClb = nullptr;
		};
	}
}

#endif //SWIPE_RPG_BOARDNODE_H