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
			NONE = 0,
			HERO,
			ITEM,
			ENEMY
		};

		struct sTilesUpgrade {
			std::string bg;
			std::string icon;
		};

		struct sTilesTypes {
			eTileTypes type;
			int attack;
			int armor;
			bool isCollect;
			bool isHero;
			bool isEnemy;
			std::map<int, sTilesUpgrade> tileUpgrade;
		};

		class tileDatabase : public databaseInterface {
		public:
			explicit tileDatabase(const std::string&);
			~tileDatabase();
			void load(const rapidjson::Document&) override;
		};
	}
}


#endif //SWIPE_RPG_TILEDATABASE_H
