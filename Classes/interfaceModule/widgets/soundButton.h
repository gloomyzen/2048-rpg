#ifndef SWIPE_RPG_SOUNDBUTTON_H
#define SWIPE_RPG_SOUNDBUTTON_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace interfaceModule {

		class soundButton : public common::coreModule::nodeProperties<cocos2d::Node> {
		public:
			soundButton();
			~soundButton();
		};

	}
}

#endif //SWIPE_RPG_SOUNDBUTTON_H
