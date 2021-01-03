#ifndef SWIPE_RPG_SCROLLHOLDER_H
#define SWIPE_RPG_SCROLLHOLDER_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace roomModule {

		class scrollHolder : public common::coreModule::nodeProperties, public cocos2d::Node, public taskHolder {
		public:
			scrollHolder();

			~scrollHolder();

			CREATE_FUNC(scrollHolder);

			std::deque<nodeTasks> getTasks() override;
		};
	}
}


#endif //SWIPE_RPG_SCROLLHOLDER_H
