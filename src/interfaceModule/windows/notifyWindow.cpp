#include "notifyWindow.h"

using namespace sr::interfaceModule;

notifyWindow::notifyWindow() {
    this->setName("notifyWindow");
    loadProperty("windows/" + this->getName(), dynamic_cast<Node*>(this));
}
std::deque<nodeTasks> notifyWindow::getTasks() {
    std::deque<nodeTasks> result;

    result.emplace_back([this]() {
        if (auto closeBtn = dynamic_cast<soundButton*>(findNode("closeBtn"))) {
            closeBtn->setOnTouch([this](cocos2d::Touch* touch, cocos2d::Event* event) { closeWindow(); });
        }

        return eTasksStatus::STATUS_OK;
    });

    result.emplace_back([this]() {
        if (auto proceedBtn = dynamic_cast<soundButton*>(findNode("proceedBtn"))) {
            proceedBtn->setOnTouch([this](cocos2d::Touch* touch, cocos2d::Event* event) {
                auto closeClb = getData<std::function<void()>>("onClose", []() {});
                if (closeClb)
                    closeClb();
                closeWindow();
            });
        }

        return eTasksStatus::STATUS_OK;
    });

    return result;
}
