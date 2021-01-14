#ifndef SWIPE_RPG_MENUBUTTON_H
#define SWIPE_RPG_MENUBUTTON_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace metaModule {

	class menuButton : public common::coreModule::nodeProperties<cocos2d::ui::Button> {
		public:
			menuButton();
			~menuButton();
			CREATE_FUNC(menuButton);
			bool init() override {
				if (!cocos2d::ui::Button::init()) {
					return false;
				}
				return true;
			}

		};
	}
}//sr::metaModule

#endif //SWIPE_RPG_MENUBUTTON_H
