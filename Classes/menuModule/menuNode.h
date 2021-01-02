#ifndef SWIPE_RPG_MENUNODE_H
#define SWIPE_RPG_MENUNODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"


namespace sr {
	namespace menuModule {

		class menuNode : public common::coreModule::nodeProperties, public cocos2d::Node, public taskHolder {
		public:
			menuNode();

			~menuNode();

			CREATE_FUNC(menuNode);

			std::deque<nodeTasks> getTasks() override;
		};
	}
}


#endif //SWIPE_RPG_MENUNODE_H
