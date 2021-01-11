#include "locationProfile.h"

using namespace sr::profileModule;

locationProfile::locationProfile() {}

locationProfile::~locationProfile() {}

bool locationProfile::load(const rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &data) {
	//todo, wip load data
	auto first = data.FindMember("forest");

	return false;
}

bool locationProfile::save(rapidjson::GenericValue<rapidjson::UTF8<char>>::ConstObject &) {
	return false;
}
