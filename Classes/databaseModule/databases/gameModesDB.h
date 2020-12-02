#ifndef SWIPE_RPG_GAMEMODESDB_H
#define SWIPE_RPG_GAMEMODESDB_H

#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <map>
#include <string>
#include "tilesDB.h"

namespace sr {
	namespace databaseModule {

		enum class eGameMode {
			UNDEFINED = -1,
			ENDLESS = 0,
		};

		struct sSpawnChance {
			int count;
			int percent;
			sSpawnChance(int _count, int _percent) : count(_count), percent(_percent) {}
		};

		struct sSpawnTile {
			sTileData tile;
			int chance;
			sSpawnTile(sTileData _tile, int _chance) : tile(std::move(_tile)), chance(_chance) {}
		};

		struct sGameModeData {
			std::string name;
			eGameMode type;
			sTileData heroTile;
			std::vector<sSpawnChance> spawnPerSwipe;
			std::vector<sSpawnTile> tiles;

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
