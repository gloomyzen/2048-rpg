#ifndef MERCENARY_BATTLES_METATABS_H
#define MERCENARY_BATTLES_METATABS_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "coreModule/nodes/nodeProperties.h"
#include "metaModule/tabs/simpleTab.h"
#include "metaModule/widgets/menuButton.h"
#include <vector>
#include <string>

namespace mb {
	namespace metaModule {
		using namespace cocos2d;
		using namespace ui;

		struct tabsElement {
			int index;
			simpleTab* tab;
			menuButton* button;
			std::string title;
		};

		class metaTabs : public coreModule::nodeProperties, public Node {
		public:
			metaTabs();
			~metaTabs();
			CREATE_FUNC(metaTabs);
			static Node *createNode() { return metaTabs::create(); }
			bool init() {
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
}//mb::metaModule


#endif //MERCENARY_BATTLES_METATABS_H
