#include "customNodeTypes.h"
#include "common/coreModule/nodes/nodeFactory.h"
///All headers
#include "battleModule/boardNode.h"
#include "battleModule/tiles/tileNode.h"
#include "interfaceModule/widgets/stateIconLabel.h"

using namespace sr::interfaceModule;

void customNodeTypes::registerAllCustomNodes() {
	GET_NODE_FACTORY().registerCustomNodeType("boardNode", []()->battleModule::boardNode* { return new battleModule::boardNode(); });
	GET_NODE_FACTORY().registerCustomNodeType("tileNode", []()->battleModule::tileNode* { return new battleModule::tileNode(); });
	GET_NODE_FACTORY().registerCustomNodeType("stateEnergyLabel", []()->interfaceModule::stateIconLabel* { return interfaceModule::stateIconLabel::generateEnergyLabel(); });
	GET_NODE_FACTORY().registerCustomNodeType("stateHealthLabel", []()->interfaceModule::stateIconLabel* { return interfaceModule::stateIconLabel::generateHealthLabel(); });
}
