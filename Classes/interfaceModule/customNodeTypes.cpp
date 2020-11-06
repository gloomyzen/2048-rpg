#include "customNodeTypes.h"
#include "common/coreModule/nodes/nodeFactory.h"
///All headers
#include "battleModule/boardNode.h"
#include "battleModule/tiles/tileNode.h"

using namespace sr::interfaceModule;

void customNodeTypes::registerAllCustomNodes() {
	GET_NODE_FACTORY().registerCustomNodeType("boardNode", []()->battleModule::boardNode* { return new battleModule::boardNode(); });
	GET_NODE_FACTORY().registerCustomNodeType("tileNode", []()->battleModule::tileNode* { return new battleModule::tileNode(); });
}
