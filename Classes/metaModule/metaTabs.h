#ifndef SWIPE_RPG_METATABS_H
#define SWIPE_RPG_METATABS_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "metaModule/tabs/simpleTab.h"
#include "metaModule/widgets/menuButton.h"
#include <vector>
#include <string>

namespace sr {
	namespace metaModule {
		using namespace cocos2d;
		using namespace ui;
		using namespace common;

		struct tabsElement {
			int index;
			simpleTab* tab;
			menuButton* button;
			std::string title;
		};

		class metaTabs : public coreModule::nodeProperties<cocos2d::Node> {
		public:
			metaTabs();
			~metaTabs();
			CREATE_FUNC(metaTabs);
			static Node *createNode() { return metaTabs::create(); }
			bool init() override {
				if (!Node::init()) {
					return false;
				}
				return true;
			}

		private:
			void createPageView();
			PageView* pageView = nullptr;
			Node* buttonHolder = nullptr;
			std::vector<tabsElement*> tabs{};

		};
	}
}//sr::metaModule


#endif //SWIPE_RPG_METATABS_H
