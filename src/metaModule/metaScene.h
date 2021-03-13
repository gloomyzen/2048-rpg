#ifndef SWIPE_RPG_METASCENE_H
#define SWIPE_RPG_METASCENE_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"

namespace sr::metaModule {

    class metaScene : public common::coreModule::nodeProperties<cocos2d::Node> {
      public:
        metaScene();
        ~metaScene() = default;

        CREATE_FUNC(metaScene);
    };
}


#endif// SWIPE_RPG_METASCENE_H
