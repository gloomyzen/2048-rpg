#ifndef SWIPE_RPG_LOCATIONPROFILE_H
#define SWIPE_RPG_LOCATIONPROFILE_H

#include "profileModule/profileBlockInterface.h"
#include "json/document.h"
#include "json/ostreamwrapper.h"

namespace sr {
	namespace profileModule {

		class locationProfile : public profileBlockInterface {
		public:
			locationProfile();
			~locationProfile() override;
			bool load(const rapidjson::Document &) override;
			bool save(rapidjson::Document &) override;
		};

	}
}


#endif //SWIPE_RPG_LOCATIONPROFILE_H
