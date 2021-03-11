#include "customNodeTypes.h"
#include "common/coreModule/nodes/nodeFactory.h"
#include "interfaceModule/widgets/cardBtnWidget.h"

//all windows
#include "interfaceModule/windows/notifyWindow.h"

using namespace sr::interfaceModule;

void customNodeTypes::registerAllCustomNodes() {
    GET_NODE_FACTORY().registerCustomNodeType("cardBtnWidget", []() { return new cardBtnWidget(); });

    // register all windows
    GET_GAME_MANAGER().registerWindow("notifyWindow", [](){ return new notifyWindow(); });
}
