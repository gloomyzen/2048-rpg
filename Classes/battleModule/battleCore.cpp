#include "battleCore.h"

using namespace sr::battleModule;

battleCore::battleCore() {
	this->setName("battleNode");
	loadProperty("battleScene/" + this->getName(), this);

	auto atp = AsyncTaskPool::getInstance();
	atp->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, [](void*){}, nullptr,
				 [this]() {
					 board = new boardNode();
					 auto rect = board->getBoundingBox();
					 Vec2 origin = rect.origin;
					 Vec2 destination;
					 auto boardSize = board->getContentSize();
					 destination.x = rect.origin.x + rect.size.width;
					 destination.y = rect.origin.y + rect.size.height;
					 clippingNode = ClippingNode::create();
					 DrawNode * stencil = DrawNode::create();
					 stencil->setName("clipperStencil");
					 stencil->drawSolidRect(origin, destination, Color4F::MAGENTA);
					 clippingNode->setStencil(stencil);
					 addChild(clippingNode);
					 clippingNode->addChild(board);
				 }
	);
}
