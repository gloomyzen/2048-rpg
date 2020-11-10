#ifndef SWIPE_RPG_TILEDATABASE_H
#define SWIPE_RPG_TILEDATABASE_H

#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <string>

namespace sr {
	namespace databaseModule {

		enum class eTileTypes {
			NONE = 0,
			HERO,
			ITEM,
			ENEMY
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
