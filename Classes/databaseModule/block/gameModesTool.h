#ifndef SWIPE_RPG_GAMEMODESTOOL_H
#define SWIPE_RPG_GAMEMODESTOOL_H

#include "databaseModule/databases/gameModesDB.h"

namespace sr {
	namespace databaseModule {
		class gameModesTool {
		public:
			gameModesTool();
			~gameModesTool();

			sTileData* getNextTile(eGameMode);
		};
	}
}


#endif //SWIPE_RPG_GAMEMODESTOOL_H
