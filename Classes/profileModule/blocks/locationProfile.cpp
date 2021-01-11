#include "locationProfile.h"

using namespace sr::profileModule;

locationProfile::locationProfile() {}

locationProfile::~locationProfile() {}

bool locationProfile::load(const rapidjson::Document &) {
	return false;
}

bool locationProfile::save(rapidjson::Document &) {
	return false;
}
