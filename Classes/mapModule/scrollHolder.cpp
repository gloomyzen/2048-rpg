#include "cocostudio/SimpleAudioEngine.h"
#include "scrollHolder.h"

using namespace sr::mapModule;
using namespace cocos2d;

scrollHolder::scrollHolder() {
	this->setName("scrollHolder");
	loadProperty("mapScene/" + this->getName(), this);
}

scrollHolder::~scrollHolder() {}

std::deque<nodeTasks> scrollHolder::getTasks() {
	std::deque<nodeTasks> result;
	result.emplace_back([this]() {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/menu.wav", true);
		scrollView = dynamic_cast<ui::ScrollView*>(findNode("scrollContainer"));
		//todo scroll by progress
//		auto bg = dynamic_cast<Sprite*>(findNode("bg"));
//		scrollView->setInnerContainerSize( cocos2d::Size(bg->getBoundingBox().size.width, bg->getBoundingBox().size.height));
//		scrollView->jumpToPercentBothDirection(Vec2(50.f, 50.f));
//		bg->setMarkDirty();

		return eTasksStatus::STATUS_OK;
	});

	result.emplace_back([this]() {
//		ui::ScrollView* scrollView = ui::ScrollView::create();
//		scrollView->setDirection(ui::ScrollView::Direction::BOTH);
//		scrollView->setContentSize( cocos2d::Size(300, 340) );
//
////		scrollView->setBackGroundImage("images/menuScene/bgMenuScene.jpg");
//		scrollView->setBounceEnabled(true);
//		scrollView->setAnchorPoint( Vec2( 0.5, 0.5 ) );
//		scrollView->setPosition( Vec2( 250, 150 ) );
//		auto sprite = Sprite::create();
//		sprite->initWithFile("images/menuScene/bgMenuScene.jpg");
//		sprite->setScale(2);
//		scrollView->addChild(sprite);
//		addChild(scrollView);

		return eTasksStatus::STATUS_OK;
	});

	return result;
}
