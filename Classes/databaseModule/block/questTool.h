#ifndef SWIPE_RPG_QUESTTOOL_H
#define SWIPE_RPG_QUESTTOOL_H

#include "cocos2d.h"
#include "databaseModule/databases/gameEnums.h"
#include "databaseModule/databases/tilesDB.h"

namespace sr {
	namespace databaseModule {

		enum class ePersonReaction {
			PERSON_SAD = 0,
			PERSON_HAPPY
		};

		struct sQuestObjective {
			eSwipeDirection direction;
			int leftSwipes = 3;
			sTileData* tile = nullptr;
			bool getSpawned() { return isSpawned; }
			bool setSpawned(bool value) { isSpawned = value; }
		private:
			bool isSpawned = false;
		};

		class questTool {
		public:
			questTool();
			~questTool();

			std::vector<sQuestObjective*> getObjectives();
			bool updateObjectives(eSwipeDirection);

		private:
			void generateNextObjective();
			void checkEndObjectives();
			std::vector<sQuestObjective*> quests;
		};
	}
}


#endif //SWIPE_RPG_QUESTTOOL_H
