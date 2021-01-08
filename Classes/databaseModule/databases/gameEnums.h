#ifndef SWIPE_RPG_GAMEENUMS_H
#define SWIPE_RPG_GAMEENUMS_H

#include <string>
#include <map>

namespace sr {
	namespace databaseModule {

		enum class eQuestEntities {
			FIND_ITEM,
			KILL_ENEMY
		};

		static const std::map<std::string, eQuestEntities> questTypeList {
				{"find_item", eQuestEntities::FIND_ITEM},
				{"kill_enemy", eQuestEntities::KILL_ENEMY},
		};

		enum class eSwipeDirection {
			UNDEFINED = 0,
			UP = 1,
			DOWN,
			LEFT,
			RIGHT
		};


	}
}

#endif //SWIPE_RPG_GAMEENUMS_H
