#include "metaScene.h"
#include <string>

using namespace sr::metaModule;


metaScene::metaScene() {
    this->setName("metaScene");
    loadProperty("scenes/" + this->getName(), dynamic_cast<Node*>(this));
}
