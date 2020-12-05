#ifndef SWIPE_RPG_TILENODE_H
#define SWIPE_RPG_TILENODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databaseModule/databaseManager.h"
#include "databaseModule/databases/tilesDB.h"

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

		private:
			sTileData* currentType = nullptr;
			Sprite* hpIcon = nullptr;
			Label* hpCountLbl = nullptr;
			Label* attackCountLbl = nullptr;

		};
	}
}

#endif //SWIPE_RPG_TILENODE_H