#ifndef SWIPE_RPG_TILENODE_H
#define SWIPE_RPG_TILENODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace battleModule {
		using namespace cocos2d;
		using namespace common;

		enum class eTileType {
			NONE = 0,
			HERO,
			ENVIRONMENT,
			ENEMY
		};

		class tileNode : public coreModule::nodeProperties, public Sprite {
		public:
			tileNode();
			~tileNode() = default;
			CREATE_FUNC(tileNode);

			void createTile(eTileType _type);

		private:
			eTileType type = eTileType::NONE;
		};
	}
}

#endif //SWIPE_RPG_TILENODE_H