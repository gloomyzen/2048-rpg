#ifndef SWIPE_RPG_PROFILEMANAGER_H
#define SWIPE_RPG_PROFILEMANAGER_H

namespace sr {
	namespace databaseModule {

		class profileManager {
		public:
			profileManager();
			~profileManager();
			static profileManager &getInstance();
		};
	}
}


#endif //SWIPE_RPG_PROFILEMANAGER_H
