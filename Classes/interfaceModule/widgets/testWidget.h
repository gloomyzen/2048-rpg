#ifndef MERCENARY_BATTLES_TESTWIDGET_H
#define MERCENARY_BATTLES_TESTWIDGET_H

#include "cocos2d.h"
#include "coreModule/nodes/nodeProperties.h"

namespace mb {
	namespace interfaceModule {
		using namespace cocos2d;

		class testWidget : public coreModule::nodeProperties, public Node {
		public:
			testWidget();
			~testWidget();

			CREATE_FUNC(testWidget);

			static Node *createNode() {
				return testWidget::create();
			}

			bool init() {
				if (!Node::init()) {
					return false;
				}
				return true;
			}

			void someMethod(){}

		};
	}
}


#endif //MERCENARY_BATTLES_TESTWIDGET_H
