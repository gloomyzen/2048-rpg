#ifndef SWIPE_RPG_SIMPLETAB_H
#define SWIPE_RPG_SIMPLETAB_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace metaModule {
		using namespace cocos2d;
		using namespace ui;
		using namespace common;

	class simpleTab : public coreModule::nodeProperties, public Layout {
		public:
			simpleTab();
			~simpleTab();
			CREATE_FUNC(simpleTab);
			static Layout *createNode() { return simpleTab::create(); }
			bool init() {
				if (!Layout::init()) {
					return false;
				}
				return true;
			}

		};
	}
}//sr::metaModule


#endif //SWIPE_RPG_SIMPLETAB_H
