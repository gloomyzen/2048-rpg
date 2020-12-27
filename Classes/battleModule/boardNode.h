#ifndef SWIPE_RPG_BOARDNODE_H
#define SWIPE_RPG_BOARDNODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "battleModule/tiles/tileNode.h"
#include "databaseModule/databases/gameEnums.h"
#include <utility>
#include <vector>
#include <map>
#include <tuple>
#include <functional>

#define BOARD_OFFSET_POS_X 10
#define BOARD_OFFSET_POS_Y 10
#define BOARD_START_POS_X 0
#define BOARD_START_POS_Y 0
#define BOARD_COUNT_X 5
#define BOARD_COUNT_Y 5
#define BOARD_HERO_POS_X 2
#define BOARD_HERO_POS_Y 2
#define BOARD_TOUCH_FORCE 75
#define BOARD_ANIMATION_DURATION 0.15f
#define BOARD_COUNT_PATTERN_X 9
#define BOARD_COUNT_PATTERN_Y 9

namespace sr {
	namespace battleModule {

		struct sSlot {
			cocos2d::Vec2 pos;
			cocos2d::Node* block = nullptr;
			tileNode* tile = nullptr;
			bool isHero = false;
			sSlot() {};
			sSlot(cocos2d::Vec2 pos, tileNode* tile, bool isHero = false) : pos(pos), tile(tile), isHero(isHero) {}
		};

		typedef std::function<bool(databaseModule::eSwipeDirection)> swipeCallback;
		typedef std::function<std::vector<databaseModule::sTileData*>()> spawnCallback;
		typedef std::function<bool(tileNode*)> heroMatchCallback;

		class boardNode : public common::coreModule::nodeProperties, public cocos2d::Node, public taskHolder {
		public:
			boardNode();
			~boardNode();
			CREATE_FUNC(boardNode);
			std::deque<nodeTasks> getTasks() override;

			void setHeroTileData(databaseModule::sTileData* heroTile);
			void initBoard();
			void setSwipeCallback(swipeCallback clb) { swipeClb = std::move(clb); }
			void setSpawnCallback(spawnCallback clb) { spawnClb = std::move(clb); }
			void setHeroMatchCallback(heroMatchCallback clb) { heroMatchClb = std::move(clb); }
			void scrollBoard(databaseModule::eSwipeDirection);
			void update(float delta) override;
			databaseModule::eTileTypes getNeighborTail(databaseModule::eSwipeDirection, int, int);

		private:
			void clearTiles();
			void setDefaultPosition();
			void generateBoardBg(cocos2d::Vec2);
			void swipeBoardBg(databaseModule::eSwipeDirection);
			void initHandling();
			void touchUpdate(cocos2d::Touch*, cocos2d::Event*);
			std::pair<int, int> getOffsetByDirection(databaseModule::eSwipeDirection, int, int);
			void swipeElements(std::vector<sSlot*> elements, bool& canSwipe);

			std::map<int, std::map<int, sSlot*>> tileMap;
			databaseModule::sTileData* heroData = nullptr;
			tileNode* heroTile = nullptr;
			cocos2d::Touch* lastTouchInfo = nullptr;
			bool isTouch = false;
			float boardTileWH;
			cocos2d::Sprite* boardBg = nullptr;
			bool boardSolid = false;
			cocos2d::Vec2 boardBgPos;
			swipeCallback swipeClb = nullptr;
			spawnCallback spawnClb = nullptr;
			heroMatchCallback heroMatchClb = nullptr;
		};
	}
}

#endif //SWIPE_RPG_BOARDNODE_H