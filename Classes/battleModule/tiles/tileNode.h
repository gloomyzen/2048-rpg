#ifndef SWIPE_RPG_TILENODE_H
#define SWIPE_RPG_TILENODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/tilesDB.h"
#include <string>

namespace sr {
	namespace battleModule {
		using namespace cocos2d;
		using namespace common;
		using namespace databaseModule;

		class tileNode : public coreModule::nodeProperties, public Node {
		public:
			tileNode();
			~tileNode() = default;
			CREATE_FUNC(tileNode);

			void createTile(const sTileData& data);
			void setTileSize(float, float);
			eTileTypes getTileType() { return tileType; }
			void setCount(int count);
			int getCount() const { return currentCnt; }
			std::string getTileDataName();


		private:
			void drawCount();

			eTileTypes tileType = eTileTypes::UNDEFINED;
			sTileData* tileData = nullptr;
			Sprite* hpIcon = nullptr;
			Label* hpCountLbl = nullptr;
			Label* attackCountLbl = nullptr;
			Label* countLbl = nullptr;
			Node* imgSlot = nullptr;
			int currentLevel = 1;
			int currentCnt = 1;
			float width = 0.f, height = 0.f;

		};
	}
}

#endif //SWIPE_RPG_TILENODE_H