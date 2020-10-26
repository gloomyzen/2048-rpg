#ifndef MERCENARY_BATTLES_MENUBUTTON_H
#define MERCENARY_BATTLES_MENUBUTTON_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "coreModule/nodes/nodeProperties.h"

namespace mb {
	namespace metaModule {
		using namespace cocos2d;
		using namespace ui;

		class menuButton : public Button, public coreModule::nodeProperties {
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
}//mb::metaModule

#endif //MERCENARY_BATTLES_MENUBUTTON_H
