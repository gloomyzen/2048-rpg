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

		struct sLevelData {
			std::string name;
			cocos2d::Vec2 pos;
			bool isBoss = false;
			bool load(const std::string& path);
		};

		class battleLevelsDB : public databaseInterface {
		public:
			explicit battleLevelsDB(const std::string &);
			~battleLevelsDB();
			void load(const rapidjson::Document &) override;

		private:
			std::map<int, sLevelData*> levelsMap;

		};
	}
}

#endif //SWIPE_RPG_BATTLELEVELSDB_H
