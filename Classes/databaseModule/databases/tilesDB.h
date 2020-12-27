#ifndef SWIPE_RPG_TILESDB_H
#define SWIPE_RPG_TILESDB_H

#include "databaseInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"
#include <string>
#include <map>
#include <functional>

namespace sr {
	namespace databaseModule {

		enum class eTileTypes {
			UNDEFINED = -1, // за пределами поля
			EMPTY = 0, //пустой тайл
			ENVIRONMENT = 1, //окружение, трава и прочее
			HERO = 2,
			ITEM = 3,
			ENEMY = 4
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
		public:
			std::string name;
			eTileTypes type = eTileTypes::EMPTY;
			int attack = 0;
			int hp = 0;
			std::map<int, sTilesUpgrade*> tileUpgrade;

			sTileData()= default;
			sTileData(const sTileData& data) {
				name = data.name;
				type = data.type;
				attack = data.attack;
				hp = data.hp;
				tileUpgrade = data.tileUpgrade;
				spawnClb = data.spawnClb;
				destroyClb = data.destroyClb;
			};
			void setSpawnClb(std::function<void()> clb) { spawnClb = std::move(clb); }
			void setDestroyClb(std::function<void()> clb) { destroyClb = std::move(clb); }
			std::function<void()>& getSpawnClb() { return spawnClb; }
			std::function<void()>& getDestroyClb() { return destroyClb; }
		private:
			std::function<void()> spawnClb = nullptr;
			std::function<void()> destroyClb = nullptr;
		};

		class tilesDB : public databaseInterface {
		public:
			explicit tilesDB(const std::string&);
			~tilesDB();
			void load(const rapidjson::Document&) override;
			sTileData* getTileByName(const std::string &name);
			bool tileExist(const std::string &name);
			std::map<std::string, sTileData*> getAllTiles() { return tileList; }

		private:
			std::map<std::string, sTileData*> tileList;
		};
	}
}


#endif //SWIPE_RPG_TILESDB_H
