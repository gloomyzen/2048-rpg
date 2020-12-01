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

		class tileNode : public coreModule::nodeProperties, public Sprite {
		public:
			tileNode();
			tileNode(float, float);
			~tileNode() = default;
			CREATE_FUNC(tileNode);

			void createTile(eTileTypes _type);

		private:
			eTileTypes type = eTileTypes::UNDEFINED;
		};
	}
}

#endif //SWIPE_RPG_TILENODE_H