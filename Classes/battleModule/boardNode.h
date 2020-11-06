#ifndef SWIPE_RPG_BOARDNODE_H
#define SWIPE_RPG_BOARDNODE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace battleModule {
		using namespace cocos2d;
		using namespace common;

		class boardNode : public coreModule::nodeProperties, public Sprite {
		public:
			boardNode();
			~boardNode();
			CREATE_FUNC(boardNode);
			static Node *createNode() { return boardNode::create(); }
			bool init() override {
				if (!Node::init()) {
					return false;
				}
				return true;
			}

		private:
		};
	}
}

#endif //SWIPE_RPG_BOARDNODE_H