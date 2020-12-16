#ifndef SWIPE_RPG_STATEICONLABEL_H
#define SWIPE_RPG_STATEICONLABEL_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace interfaceModule {

		class stateIconLabel : public common::coreModule::nodeProperties, public cocos2d::Node {
		public:
			stateIconLabel();
			~stateIconLabel() = default;

			CREATE_FUNC(stateIconLabel);

			static Node *createNode() {
				return stateIconLabel::create();
			}

			bool init() {
				if (!Node::init()) {
					return false;
				}
				return true;
			}
		};
	}
}


#endif //SWIPE_RPG_STATEICONLABEL_H
