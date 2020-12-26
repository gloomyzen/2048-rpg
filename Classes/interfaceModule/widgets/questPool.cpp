#include "questPool.h"
#include <map>

using namespace sr::interfaceModule;
using namespace sr::databaseModule;

std::map<eSwipeDirection, std::string> arrowImages = {
		{eSwipeDirection::UP, "images/widgets/questPool/arrowUp.png"},
		{eSwipeDirection::DOWN, "images/widgets/questPool/arrowDown.png"},
		{eSwipeDirection::LEFT, "images/widgets/questPool/arrowLeft.png"},
		{eSwipeDirection::RIGHT, "images/widgets/questPool/arrowRight.png"},
};

//todo now it is not used
std::map<ePersonReaction, std::string> personImages = {
		{ePersonReaction::PERSON_SAD, "images/widgets/questPool/personSad.png"},
		{ePersonReaction::PERSON_HAPPY, "images/widgets/questPool/personHappy.png"},
};

questPool::questPool() {
	this->setName("questPool");
	loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
	arrowHolder = dynamic_cast<Node*>(findNode("arrowHolder"));
	if (!arrowHolder) {
		LOG_ERROR("questPool::questPool() Can't find element 'arrowHolder'!");
	}
	personHolder = dynamic_cast<Node*>(findNode("personHolder"));
	if (!personHolder) {
		LOG_ERROR("questPool::questPool() Can't find element 'personHolder'!");
	}
}

void questPool::printQuest(databaseModule::sQuestObjective*) {

}
