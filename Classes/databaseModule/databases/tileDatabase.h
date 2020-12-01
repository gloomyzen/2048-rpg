#ifndef SWIPE_RPG_TILEDATABASE_H
#define SWIPE_RPG_TILEDATABASE_H

#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <string>
#include <map>

#if defined(_MSC_VER) && defined(GetObject)
#undef GetObject
#endif

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

		struct sTilesTypes {
			std::string name;
			eTileTypes type = eTileTypes::UNDEFINED;
			int attack = 0;
			int hp = 0;
			std::map<int, sTilesUpgrade> tileUpgrade;
		};

		class tileDatabase : public databaseInterface {
		public:
			explicit tileDatabase(const std::string&);
			~tileDatabase();
			void load(const rapidjson::Document&) override;
			sTilesTypes getTileByName(const std::string &name);
			bool tileExist(const std::string &name);
			std::map<std::string, sTilesTypes> getAllTiles() { return tileList; }

		private:
			std::map<std::string, sTilesTypes> tileList;
		};
	}
}


#endif //SWIPE_RPG_TILEDATABASE_H
