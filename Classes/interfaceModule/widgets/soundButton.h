#ifndef SWIPE_RPG_SOUNDBUTTON_H
#define SWIPE_RPG_SOUNDBUTTON_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/eventNode.h"
#include <string>
#include <functional>

namespace sr {
	namespace interfaceModule {

		class soundButton : public common::coreModule::nodeProperties<cocos2d::Sprite>, public common::coreModule::eventNode {
		public:
			soundButton();
			~soundButton() override;

			void setClickCallback(std::function<void()>);
		private:
			std::function<void()> soundCallback = nullptr;
			std::function<void()> onClickCallback = nullptr;
//			cocos2d::EventListenerTouchOneByOne* listener = nullptr;

		};

	}
}

#endif //SWIPE_RPG_SOUNDBUTTON_H
