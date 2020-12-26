#ifndef SWIPE_RPG_QUESTPOOL_H
#define SWIPE_RPG_QUESTPOOL_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "databaseModule/block/questTool.h"
#include <string>

namespace sr {
	namespace interfaceModule {
		class questPool : public common::coreModule::nodeProperties, public cocos2d::Node {
		public:
			questPool();
			~questPool() = default;

			CREATE_FUNC(questPool);

			static Node *createNode() {
				return questPool::create();
			}

			bool init() {
				if (!Node::init()) {
					return false;
				}
				return true;
			}

			void printQuest(databaseModule::sQuestObjective*);

		};
	}
}

#endif //SWIPE_RPG_QUESTPOOL_H
