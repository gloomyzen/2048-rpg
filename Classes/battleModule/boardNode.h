#ifndef SWIPE_RPG_BOARDNODE_H
#define SWIPE_RPG_BOARDNODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "battleModule/tiles/tileNode.h"
#include <utility>
#include <vector>
#include <map>
#include <tuple>
#include <functional>

#define BOARD_START_POS_X 0
#define BOARD_START_POS_Y 0
#define BOARD_COUNT_X 5
#define BOARD_COUNT_Y 5
#define BOARD_HERO_POS_X 1
#define BOARD_HERO_POS_Y 2
#define BOARD_TOUCH_FORCE 75

namespace sr {
	namespace battleModule {
		using namespace cocos2d;
		using namespace common;

		struct sSlot {
			cocos2d::Vec2 pos;
			tileNode* tile = nullptr;
			bool isHero = false;
			sSlot() {};
			sSlot(cocos2d::Vec2 pos, tileNode* tile, bool isHero = false) : pos(pos), tile(tile), isHero(isHero) {}
		};

		enum class eSwipeDirection {
			UNDEFINED = 0,
			UP = 1,
			DOWN,
			LEFT,
			RIGHT
		};

		typedef std::function<bool(eSwipeDirection)> swipeCallback;
		typedef std::function<std::vector<sTileData *>()> spawnCallback;

		class boardNode : public coreModule::nodeProperties, public Sprite, public taskHolder {
		public:
			boardNode();
			~boardNode();
			CREATE_FUNC(boardNode);
			std::deque<nodeTasks> getTasks() override;

			void setHeroTileData(sTileData* heroTile);
			void initBoard();
			void setSwipeCallback(swipeCallback clb) { swipeClb = std::move(clb); }
			void setSpawnCallback(spawnCallback clb) { spawnClb = std::move(clb); }
			void scrollBoard(eSwipeDirection);
			void update(float delta) override;
			eTileTypes getNeighborTail(eSwipeDirection, int, int);

		private:
			void clearTiles();
			void setDefaultPosition();
			void initHandling();
			void touchUpdate(Touch*, Event*);
			std::pair<int, int> getOffsetByDirection(eSwipeDirection, int, int);

			std::map<int, std::map<int, sSlot*>> tileMap;
			sTileData* heroData = nullptr;
			Touch* lastTouchInfo = nullptr;
			bool isTouch = false;
			swipeCallback swipeClb = nullptr;
			spawnCallback spawnClb = nullptr;
		};
	}
}

#endif //SWIPE_RPG_BOARDNODE_H