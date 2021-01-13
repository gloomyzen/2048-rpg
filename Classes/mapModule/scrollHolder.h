#ifndef SWIPE_RPG_SCROLLHOLDER_H
#define SWIPE_RPG_SCROLLHOLDER_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "ui/CocosGUI.h"
#include "databaseModule/databases/battleLevelsDB.h"
#include "profileModule/blocks/locationProfile.h"
#include <vector>

namespace sr {
	namespace mapModule {

		class scrollHolder : public common::coreModule::nodeProperties, public cocos2d::Node, public taskHolder {
			struct sMapPiece {
				databaseModule::sLevelDataPiece* pieceData = nullptr;
				profileModule::sLocationLog* quest = nullptr;
				cocos2d::Node* pieceNode = nullptr;
				sMapPiece(databaseModule::sLevelDataPiece* data, profileModule::sLocationLog* questLog, cocos2d::Node* node) :
				pieceData(data), quest(questLog), pieceNode(node) {}
			};
		public:
			scrollHolder();
			~scrollHolder();
			CREATE_FUNC(scrollHolder);

			std::deque<nodeTasks> getTasks() override;

		private:
			cocos2d::ui::ScrollView* scrollView = nullptr;
			std::vector<sMapPiece*> piecesList;
		};
	}
}


#endif //SWIPE_RPG_SCROLLHOLDER_H
