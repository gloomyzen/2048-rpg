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

		private:
			void updateArrow(databaseModule::eSwipeDirection);
			void updatePersonReaction(databaseModule::ePersonReaction);
			cocos2d::Node* arrowHolder = nullptr;
			cocos2d::Node* personHolder = nullptr;
			cocos2d::Label* countLabel = nullptr;
		};
	}
}

#endif //SWIPE_RPG_QUESTPOOL_H
