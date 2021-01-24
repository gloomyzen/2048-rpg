#include "customNodeTypes.h"
#include "common/coreModule/nodes/nodeFactory.h"
///All headers
#include "interfaceModule/widgets/soundButton.h"
#include "battleModule/boardNode.h"
#include "battleModule/tiles/tileNode.h"
#include "interfaceModule/widgets/stateIconLabel.h"
#include "interfaceModule/widgets/questPool.h"

using namespace sr::interfaceModule;

void customNodeTypes::registerAllCustomNodes() {
	GET_NODE_FACTORY().registerCustomNodeType("soundButton", []() { return new interfaceModule::soundButton(); });
	GET_NODE_FACTORY().registerCustomNodeType("boardNode", []() { return new battleModule::boardNode(); });
	GET_NODE_FACTORY().registerCustomNodeType("tileNode", []() { return new battleModule::tileNode(); });
	GET_NODE_FACTORY().registerCustomNodeType("stateEnergyLabel", []() { return interfaceModule::stateIconLabel::generateEnergyLabel(); });
	GET_NODE_FACTORY().registerCustomNodeType("stateHealthLabel", []() { return interfaceModule::stateIconLabel::generateHealthLabel(); });
	GET_NODE_FACTORY().registerCustomNodeType("questPoolWidget", []() { return new interfaceModule::questPool(); });
}
