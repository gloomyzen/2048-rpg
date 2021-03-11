#ifndef SWIPE_RPG_CARDBTNWIDGET_H
#define SWIPE_RPG_CARDBTNWIDGET_H

#include "cocos2d.h"
#include "common/coreModule/nodes/nodeProperties.h"
#include "common/coreModule/nodes/widgets/soundButton.h"

namespace sr::interfaceModule {

    class cardBtnWidget : public common::coreModule::soundButton {
      public:
        cardBtnWidget();
        ~cardBtnWidget() = default;

        CREATE_FUNC(cardBtnWidget);

        void setText(const std::string&);

      private:
        cocos2d::Label* label = nullptr;
    };
}// namespace sr::interfaceModule

#endif// SWIPE_RPG_CARDBTNWIDGET_H
