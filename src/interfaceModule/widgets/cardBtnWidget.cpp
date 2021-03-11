#include "cardBtnWidget.h"
#include "cocos-ext.h"

using namespace sr::interfaceModule;

cardBtnWidget::cardBtnWidget() {
    this->setName("cardBtnWidget");
    loadProperty("widgets/" + this->getName(), dynamic_cast<Node*>(this));
    bgNode = dynamic_cast<cocos2d::ui::Scale9Sprite*>(findNode("cardBg"));
    label = dynamic_cast<cocos2d::Label*>(findNode("btnText"));
}

void cardBtnWidget::setText(const std::string& value) { label->setString(value); }
