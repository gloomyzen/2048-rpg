#include "questPool.h"
#include "cocos2d.h"
#include <map>

using namespace sr::interfaceModule;
using namespace sr::databaseModule;

std::map<eSwipeDirection, std::string> arrowImages = {
		{eSwipeDirection::UP, "images/widgets/questPool/arrowUp.png"},
		{eSwipeDirection::DOWN, "images/widgets/questPool/arrowDown.png"},
		{eSwipeDirection::LEFT, "images/widgets/questPool/arrowLeft.png"},
		{eSwipeDirection::RIGHT, "images/widgets/questPool/arrowRight.png"},
};

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
	countLabel = dynamic_cast<cocos2d::Label*>(findNode("leftStepsLabel"));
	if (!countLabel) {
		LOG_ERROR("questPool::questPool() Can't find element 'leftStepsLabel'!");
	}
}

void questPool::printQuest(databaseModule::sQuestObjective* quest) {
	if (arrow) {
		arrow->setVisible(false);
	}
	if (person) {
		person->setVisible(false);
	}
	countLabel->setVisible(false);

	if (quest->direction == eSwipeDirection::UNDEFINED) {
		LOG_ERROR("questPool::printQuest() 'UNDEFINED' swipe action!");
		return;
	}

	if (quest->leftSwipes > 0) {
		//add image arrow label and person
		updateArrow(quest->direction);
		countLabel->setVisible(true);
		countLabel->setString(std::to_string(quest->leftSwipes));
		updatePersonReaction(ePersonReaction::PERSON_SAD);
	} else if (quest->leftSwipes == 0) {
		//add only person
		updatePersonReaction(ePersonReaction::PERSON_HAPPY);
	}

}

void questPool::updateArrow(databaseModule::eSwipeDirection direction) {
	if (!arrow) {
		arrow = cocos2d::Sprite::create();
		arrowHolder->addChild(arrow);
	}
	auto arrowImg = arrowImages.find(direction);
	if (arrowImg != arrowImages.end()) {
		arrow->initWithFile(arrowImg->second);
	}
	arrow->setVisible(true);
}

void questPool::updatePersonReaction(ePersonReaction state) {
	if (!person) {
		person = cocos2d::Sprite::create();
		personHolder->addChild(person);
	}
	auto reactionImg = personImages.find(state);
	if (reactionImg != personImages.end()) {
		person->initWithFile(reactionImg->second);
	}
	person->setVisible(true);
}
