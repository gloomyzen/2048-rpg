#include "customNodeTypes.h"
#include "common/coreModule/nodes/nodeFactory.h"
///All headers
#include "battleModule/board.h"
#include "battleModule/tiles/tileNode.h"

using namespace sr::interfaceModule;

void customNodeTypes::registerAllCustomNodes() {
	GET_NODE_FACTORY().registerCustomNodeType("boardNode", []()->battleModule::board* { return new battleModule::board(); });
	GET_NODE_FACTORY().registerCustomNodeType("tileNode", []()->battleModule::tileNode* { return new battleModule::tileNode(); });
}
