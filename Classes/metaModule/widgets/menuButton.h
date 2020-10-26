#ifndef SWIPE_RPG_MENUBUTTON_H
#define SWIPE_RPG_MENUBUTTON_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace metaModule {
		using namespace cocos2d;
		using namespace ui;

	class menuButton : public Button, public common::coreModule::nodeProperties {
		public:
			menuButton();
			~menuButton();
			CREATE_FUNC(menuButton);
			bool init() override {
				if (!Button::init()) {
					return false;
				}
				return true;
			}

		};
	}
}//sr::metaModule

#endif //SWIPE_RPG_MENUBUTTON_H
