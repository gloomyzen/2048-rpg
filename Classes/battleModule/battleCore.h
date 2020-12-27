#ifndef SWIPE_RPG_BATTLECORE_H
#define SWIPE_RPG_BATTLECORE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "boardNode.h"
#include "databaseModule/block/questTool.h"
#include "databaseModule/databases/tilesDB.h"
#include "interfaceModule/widgets/questPool.h"

namespace sr {
	namespace battleModule {

		class battleCore : public common::coreModule::nodeProperties, public cocos2d::Node, public taskHolder {
		public:
			battleCore();
			~battleCore() = default;
			CREATE_FUNC(battleCore);

			std::deque<nodeTasks> getTasks() override;

		private:
			void updateStats();
			void update(float delta) override;
			std::vector<databaseModule::sTileData*> tilesToSpawn;
			boardNode* board = nullptr;
			cocos2d::ClippingNode* clippingNode = nullptr;
			cocos2d::Label* hpLbl = nullptr;
			cocos2d::Label* energyLbl = nullptr;
			int currentEnergy;
			int currentHp;
			databaseModule::questTool* questMgr = nullptr;
			interfaceModule::questPool* questList = nullptr;
			time_t swipeTimer;
			bool swipeAvailable = true;
			cocos2d::Scheduler* scheduler = nullptr;
		};
	}
}


#endif //SWIPE_RPG_BATTLECORE_H
