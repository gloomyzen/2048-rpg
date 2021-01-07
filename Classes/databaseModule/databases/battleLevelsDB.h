#ifndef SWIPE_RPG_BATTLELEVELSDB_H
#define SWIPE_RPG_BATTLELEVELSDB_H

#include "cocos2d.h"
#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <string>
#include <map>

namespace sr {
	namespace databaseModule {

		enum class eBattleLevelsTypes {
			FOREST_LEVEL,
			CAVE_LEVEL,
			CRYSTAL_LEVEL,
			LAVA_LEVEL,
		};

		struct sLevelData {
			std::string locationName;
			std::map<cocos2d::Vec2, std::string> currentMap;
			bool load(const std::string& path);
		};

		class battleLevelsDB : public databaseInterface {
		public:
			explicit battleLevelsDB(const std::string &);
			~battleLevelsDB();
			void load(const rapidjson::Document &) override;

			std::map<eBattleLevelsTypes, sLevelData*> getLevelsData() { return levelsMap; }

		private:
			std::map<eBattleLevelsTypes, sLevelData*> levelsMap;

		};
	}
}

#endif //SWIPE_RPG_BATTLELEVELSDB_H
