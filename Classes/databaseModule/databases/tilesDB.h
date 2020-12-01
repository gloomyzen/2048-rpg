#ifndef SWIPE_RPG_TILESDB_H
#define SWIPE_RPG_TILESDB_H

#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <string>
#include <map>

namespace sr {
	namespace databaseModule {

		enum class eTileTypes {
			UNDEFINED = -1,
			ENVIRONMENT = 0,
			HERO = 1,
			ITEM = 2,
			ENEMY = 3
		};

		struct sTilesUpgrade {
			explicit sTilesUpgrade(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject& object);

			int id = 0;
			std::string bg;
			std::string icon;

			bool isValid() const {
				return id > 0 && !bg.empty();
			}
		};

		struct sTileData {
			std::string name;
			eTileTypes type = eTileTypes::UNDEFINED;
			int attack = 0;
			int hp = 0;
			std::map<int, sTilesUpgrade> tileUpgrade;
		};

		class tilesDB : public databaseInterface {
		public:
			explicit tilesDB(const std::string&);
			~tilesDB();
			void load(const rapidjson::Document&) override;
			sTileData getTileByName(const std::string &name);
			bool tileExist(const std::string &name);
			std::map<std::string, sTileData> getAllTiles() { return tileList; }

		private:
			std::map<std::string, sTileData> tileList;
		};
	}
}


#endif //SWIPE_RPG_TILESDB_H
