#ifndef SWIPE_RPG_TILEDATABASE_H
#define SWIPE_RPG_TILEDATABASE_H

#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <string>
#include <map>

namespace sr {
	namespace databaseModule {

		enum class eTileTypes {
			UNDEFINED = 0,
			NONE,
			HERO,
			ITEM,
			ENEMY
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
			int armor = 0;
			bool isCollect = false;
			bool isHero = false;
			bool isEnemy = false;
			std::map<int, sTilesUpgrade> tileUpgrade;
		};

		class tileDatabase : public databaseInterface {
		public:
			explicit tileDatabase(const std::string&);
			~tileDatabase();
			void load(const rapidjson::Document&) override;

		private:
			std::map<std::string, sTilesTypes> tileList;
		};
	}
}


#endif //SWIPE_RPG_TILEDATABASE_H
