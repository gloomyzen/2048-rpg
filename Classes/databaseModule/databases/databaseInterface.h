#ifndef SWIPE_RPG_DATABASEINTERFACE_H
#define SWIPE_RPG_DATABASEINTERFACE_H

#include "json/document.h"
#include "json/ostreamwrapper.h"
#include "common/debugModule/logManager.h"

namespace sr {
	namespace databaseModule {
		class databaseInterface {
		public:
			virtual ~databaseInterface() = default;
			virtual void load(const rapidjson::Document&) = 0;
			bool isValidJson(const rapidjson::Document& data) {
				if (data.HasParseError()) {
					LOG_ERROR("isValidJson: json parse error");
					return false;
				}

				if (data.IsNull()) {
					LOG_ERROR("isValidJson: json is empty");
					return false;
				}
				return true;
			}
		};
	}
}

#endif //SWIPE_RPG_DATABASEINTERFACE_H
