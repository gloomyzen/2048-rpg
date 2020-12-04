#ifndef SWIPE_RPG_GAMEMODESTOOL_H
#define SWIPE_RPG_GAMEMODESTOOL_H

#include "databaseModule/databases/gameModesDB.h"
#include "databaseModule/databaseManager.h"

namespace sr {
	namespace databaseModule {
		class gameModesTool {
		public:
			gameModesTool();
			~gameModesTool();

			static sTileData* getNextTile(eGameMode);

		};
	}
}


#endif //SWIPE_RPG_GAMEMODESTOOL_H
