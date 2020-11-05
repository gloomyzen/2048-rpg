#ifndef SWIPE_RPG_BOARD_H
#define SWIPE_RPG_BOARD_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr {
	namespace battleModule {
		using namespace cocos2d;
		using namespace common;

		class board : public coreModule::nodeProperties, public Node {
		public:
			board();
			~board() = default;
			CREATE_FUNC(board);
			static Node *createNode() { return board::create(); }
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

#endif //SWIPE_RPG_BOARD_H