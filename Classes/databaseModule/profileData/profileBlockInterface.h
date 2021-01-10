#ifndef SWIPE_RPG_PROFILEBLOCKINTERFACE_H
#define SWIPE_RPG_PROFILEBLOCKINTERFACE_H

#include "json/document.h"
#include "json/ostreamwrapper.h"

namespace sr {
	namespace databaseModule {

		class profileBlockInterface {
		public:
			virtual ~profileBlockInterface() = default;
			virtual bool load(const rapidjson::Document &) = 0;
			virtual bool save(rapidjson::Document &) = 0;
		};
	}
}

#endif //SWIPE_RPG_PROFILEBLOCKINTERFACE_H
