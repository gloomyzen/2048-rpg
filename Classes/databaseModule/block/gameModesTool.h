#ifndef SWIPE_RPG_GAMEMODESTOOL_H
#define SWIPE_RPG_GAMEMODESTOOL_H

#include "databaseModule/databases/gameModesDB.h"
#include "databaseModule/databaseManager.h"
#include <vector>

namespace sr {
	namespace databaseModule {
		class gameModesTool {
		public:
			gameModesTool();
			~gameModesTool();

			static std::vector<sTileData*> getNextTile(eGameMode);

		};
	}
}


#endif //SWIPE_RPG_GAMEMODESTOOL_H
