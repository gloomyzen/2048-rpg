#ifndef SWIPE_RPG_TILENODE_H
#define SWIPE_RPG_TILENODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/tilesDB.h"
#include <string>

namespace sr {
	namespace battleModule {
		using namespace common;
		using namespace databaseModule;

		class tileNode : public coreModule::nodeProperties, public cocos2d::Node {
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
			void calculateCount(tileNode*);
			bool canMatchTile(tileNode*);
			sTileData* getTileData() { return tileData; }

		private:
			void drawCount();
			void updateTileFromData();

			eTileTypes tileType = eTileTypes::UNDEFINED;
			sTileData* tileData = nullptr;
			cocos2d::Sprite* hpIcon = nullptr;
			cocos2d::Label* hpCountLbl = nullptr;
			cocos2d::Label* attackCountLbl = nullptr;
			cocos2d::Label* countLbl = nullptr;
			cocos2d::Node* imgSlot = nullptr;
			int currentCnt = 1;
			float width = 0.f, height = 0.f;

		};
	}
}

#endif //SWIPE_RPG_TILENODE_H