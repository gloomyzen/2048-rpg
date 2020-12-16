#ifndef SWIPE_RPG_TESTWIDGET_H
#define SWIPE_RPG_TESTWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace interfaceModule {

	class testWidget : public common::coreModule::nodeProperties, public cocos2d::Node {
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
}//sr::interfaceModule


#endif //SWIPE_RPG_TESTWIDGET_H
