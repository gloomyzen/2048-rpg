#ifndef SWIPE_RPG_NOTIFYWINDOW_H
#define SWIPE_RPG_NOTIFYWINDOW_H

#include "cocos2d.h"
#include "common/coreModule/scenes/windows/windowBase.h"

namespace sr::interfaceModule {

    class notifyWindow
        : public common::coreModule::windowBase
        , public taskHolder {
      public:
        notifyWindow();
        ~notifyWindow() = default;
        std::deque<nodeTasks> getTasks() override;
    };
}// namespace sr::interfaceModule


#endif// SWIPE_RPG_NOTIFYWINDOW_H
