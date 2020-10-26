#include "metaTabs.h"
#include "cocos2d.h"

using namespace mb::metaModule;
using namespace cocos2d;
using namespace ui;


metaTabs::metaTabs() {
	this->setName("metaTabs");
	createPageView();
	loadProperty("menuScene/" + this->getName(), dynamic_cast<Node *>(this));
}

metaTabs::~metaTabs() {}

void metaTabs::createPageView() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	pageView = PageView::create();
	pageView->setName("tabsHolder");
	pageView->setDirection(PageView::Direction::HORIZONTAL);
	pageView->setMagneticType(ListView::MagneticType::CENTER);
	pageView->setGravity(ListView::Gravity::CENTER_HORIZONTAL);
	pageView->setPosition(Vec2());
	pageView->setContentSize(visibleSize);
	pageView->setBounceEnabled(true);
	this->addChild(pageView);

	buttonHolder = Node::create();
	addChild(buttonHolder);

	{//simple page
		auto page = new tabsElement();
		page->index = tabs.size();
		page->tab = new simpleTab();
		page->tab->setContentSize(pageView->getContentSize());
		pageView->addPage(page->tab);
		page->title = "Missions";
		tabs.push_back(page);
	};
	{//battle page
		auto page = new tabsElement();
		page->index = tabs.size();
		page->tab = new simpleTab();
		page->tab->setContentSize(pageView->getContentSize());
		pageView->addPage(page->tab);
		page->title = "Campaign";
		tabs.push_back(page);
	};
	{//simple page
		auto page = new tabsElement();
		page->index = tabs.size();
		page->tab = new simpleTab();
		page->tab->setContentSize(pageView->getContentSize());
		pageView->addPage(page->tab);
		page->title = "Heroes";
		tabs.push_back(page);
	};

	//set default opened page
	pageView->setCurrentPageIndex(1);

	if (buttonHolder != nullptr) {
		float offset = 0.f;
		float offsetX = 15.f;
		for (auto item : tabs) {
			item->button = new menuButton();
			buttonHolder->addChild(item->button);
			item->button->setPosition(Vec2(offset, 0.f));
			offset += item->button->getContentSize().width + offsetX;
			item->button->addTouchEventListener([this, item](Ref* sender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED) {
					pageView->scrollToItem(item->index);
				}
			});
		}
		buttonHolder->setAnchorPoint(Vec2::ZERO);
		buttonHolder->setContentSize(cocos2d::Size(offset, tabs.front()->button->getContentSize().height));
		buttonHolder->setPosition(Vec2((visibleSize.width/2) - (offset / 2), 0));
	}



	/*pageView->addEventListener([](Ref *sender, ui::PageView::EventType type) {
		if (type == ui::PageView::EventType::TURNING) {
			auto _pageView = dynamic_cast<PageView *>(sender);
			if (_pageView != nullptr) {
				CCLOG("current page no =%zd", _pageView->getCurrentPageIndex());
			}
		}
	});*/

}
