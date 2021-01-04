#ifndef SWIPE_RPG_SCROLLHOLDER_H
#define SWIPE_RPG_SCROLLHOLDER_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "ui/CocosGUI.h"

namespace sr {
	namespace mapModule {

		class scrollHolder : public common::coreModule::nodeProperties, public cocos2d::Node, public taskHolder {
		public:
			scrollHolder();
			~scrollHolder();
			CREATE_FUNC(scrollHolder);

			std::deque<nodeTasks> getTasks() override;
			cocos2d::ui::ScrollView* scrollView = nullptr;
		};
	}
}


#endif //SWIPE_RPG_SCROLLHOLDER_H
