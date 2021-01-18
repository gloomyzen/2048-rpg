#ifndef SWIPE_RPG_SOUNDBUTTON_H
#define SWIPE_RPG_SOUNDBUTTON_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include <string>
#include <functional>

namespace sr {
	namespace interfaceModule {

		class soundButton : public common::coreModule::nodeProperties<cocos2d::Sprite> {
		public:
			soundButton();
			~soundButton() override;

			void setClickable(bool value) { clickable = value; }
			bool isClickable() const { return clickable; }
			void setClickCallback(std::function<void()>);
		private:
			std::function<void()> soundCallback = nullptr;
			std::function<void()> onClickCallback = nullptr;
			bool clickable = true;
			cocos2d::EventListenerTouchOneByOne* listener = nullptr;

		};

	}
}

#endif //SWIPE_RPG_SOUNDBUTTON_H
