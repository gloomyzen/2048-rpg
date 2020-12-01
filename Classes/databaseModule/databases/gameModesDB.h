#ifndef SWIPE_RPG_GAMEMODESDB_H
#define SWIPE_RPG_GAMEMODESDB_H

#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <map>
#include "tilesDB.h"

namespace sr {
	namespace databaseModule {

		enum class eGameMode {
			UNDEFINED = -1,
			ENDLESS = 0,
		};

		struct sGameModeData {
			std::string name;
			eGameMode type;
			sTileData heroTile;
			//todo
//			spawnPerSwipe <- array of structs
			//todo
//			tiles <- array of structs

		};

		class gameModesDB : public databaseInterface {
		public:
			explicit gameModesDB(const std::string&);
			~gameModesDB();
			void load(const rapidjson::Document&) override;


		private:
			std::map<eGameMode, sGameModeData> modesList;
		};

	}
}


#endif //SWIPE_RPG_GAMEMODESDB_H
