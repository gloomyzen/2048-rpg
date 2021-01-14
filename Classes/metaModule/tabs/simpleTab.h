#ifndef SWIPE_RPG_SIMPLETAB_H
#define SWIPE_RPG_SIMPLETAB_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace metaModule {

	class simpleTab : public common::coreModule::nodeProperties<cocos2d::ui::Layout> {
		public:
			simpleTab();
			~simpleTab();
			CREATE_FUNC(simpleTab);
			static cocos2d::ui::Layout *createNode() { return simpleTab::create(); }
			bool init() {
				if (!cocos2d::ui::Layout::init()) {
					return false;
				}
				return true;
			}

		};
	}
}//sr::metaModule


#endif //SWIPE_RPG_SIMPLETAB_H
