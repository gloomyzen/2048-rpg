#ifndef SWIPE_RPG_BATTLELEVELSDB_H
#define SWIPE_RPG_BATTLELEVELSDB_H

#include "cocos2d.h"
#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include "databaseModule/databases/gameEnums.h"
#include <string>
#include <map>
#include <vector>

namespace sr {
	namespace databaseModule {

		struct sLevelDataPiece {
			int id;
			int row;
			cocos2d::Vec2 position;
			std::string nodeName;
			std::string property;
			bool heroStart = false;
			std::vector<unsigned int> quests;
		};

		struct sLevelData {
			std::string locationName;
			std::map<int, sLevelDataPiece*> currentMap; //id + struct
			bool load(const std::string& path);
			sLevelDataPiece* getDataPieceById(int);
		};

		class battleLevelsDB : public databaseInterface {
		public:
			explicit battleLevelsDB(const std::string &);
			~battleLevelsDB();
			void load(const rapidjson::Document &) override;

			std::map<eBattleLevelsTypes, sLevelData*> getLevelsData() { return levelsMap; }
			sLevelData* getDataByLevel(databaseModule::eBattleLevelsTypes);

		private:
			std::map<eBattleLevelsTypes, sLevelData*> levelsMap;

		};
	}
}

#endif //SWIPE_RPG_BATTLELEVELSDB_H
