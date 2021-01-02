#include "cocostudio/SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "menuNode.h"

using namespace sr::menuModule;
using namespace cocos2d;

menuNode::menuNode() {
//	this->setName("menuNode");
//	loadProperty("menuScene/" + this->getName(), this);
}

menuNode::~menuNode() {}

std::deque<nodeTasks> menuNode::getTasks() {
	std::deque<nodeTasks> result;
	result.emplace_back([this]() {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/menu.wav", true);

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
		ui::ScrollView* scrollView = ui::ScrollView::create();
		scrollView->setDirection(ui::ScrollView::Direction::BOTH);
		scrollView->setContentSize( cocos2d::Size(300, 340) );

		scrollView->setBackGroundImage("images/menuScene/bgMenuScene.jpg");
		//scrollView->setBounceEnabled(true);
		scrollView->setAnchorPoint( Vec2( 0.5, 0.5 ) );
		scrollView->setPosition( Vec2( 250, 150 ) );

		addChild(scrollView);

		return eTasksStatus::STATUS_OK;
	});

	return result;
}
