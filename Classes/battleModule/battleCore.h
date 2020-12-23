#ifndef SWIPE_RPG_BATTLECORE_H
#define SWIPE_RPG_BATTLECORE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "boardNode.h"

namespace sr {
	namespace battleModule {
	using namespace common;

		class battleCore : public coreModule::nodeProperties, public cocos2d::Node, public taskHolder {
		public:
			battleCore();
			~battleCore() = default;
			CREATE_FUNC(battleCore);

			std::deque<nodeTasks> getTasks() override;

		private:
			void updateStats();
			boardNode* board = nullptr;
			cocos2d::ClippingNode* clippingNode = nullptr;
			cocos2d::Label* hpLbl = nullptr;
			cocos2d::Label* energyLbl = nullptr;
			int currentEnergy;
			int currentHp;
		};
	}
}


#endif //SWIPE_RPG_BATTLECORE_H
