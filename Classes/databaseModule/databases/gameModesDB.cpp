#include "gameModesDB.h"

using namespace sr;
using namespace sr::databaseModule;

static std::map<std::string, eGameMode> gmTypesMap = {
		{"endless", eGameMode::ENDLESS},
};

gameModesDB::gameModesDB(const std::string &) {}

gameModesDB::~gameModesDB() {}

void gameModesDB::load(const rapidjson::Document &) {}
