#include "battleCore.h"

using namespace sr::battleModule;

battleCore::battleCore() {
	this->setName("battleNode");
	loadProperty("battleScene/" + this->getName(), this);

	auto atp = AsyncTaskPool::getInstance();
	atp->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, [](void*){}, nullptr,
				 [this]() {
					 board = dynamic_cast<boardNode*>(findNode("boardNode", this));
					 auto test = "";
				 }
	);
}
