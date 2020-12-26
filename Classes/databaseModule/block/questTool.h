#ifndef SWIPE_RPG_QUESTTOOL_H
#define SWIPE_RPG_QUESTTOOL_H

#include "cocos2d.h"
#include "databaseModule/databases/gameEnums.h"

namespace sr {
	namespace databaseModule {

		struct sQuestObjective {
			eSwipeDirection direction;
			int leftSwipes = 3;
		};

		class questTool {
		public:
			questTool();
			~questTool();

			std::vector<sQuestObjective*> getObjectives();
			bool updateObjectives(eSwipeDirection);

		private:
			void generateNextObjective();
			std::vector<sQuestObjective*> quests;
		};
	}
}


#endif //SWIPE_RPG_QUESTTOOL_H
