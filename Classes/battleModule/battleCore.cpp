#include "battleCore.h"

using namespace sr::battleModule;

battleCore::battleCore() {
	this->setName("battleNode");
	loadProperty("battleScene/" + this->getName(), this);
//	board = new boardNode();
//	addChild(board);
}
