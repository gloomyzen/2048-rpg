#include "metaScene.h"
#include <string>

using namespace sr::metaModule;


metaScene::metaScene() {
    this->setName("metaScene");
    loadProperty("scenes/" + this->getName(), dynamic_cast<Node*>(this));
    auto vertFilename = std::string("shaders/shader").append(".vsh");
    auto fragFilename = std::string("shaders/shader").append(".fsh");
    auto glprogram = GLProgram::createWithFilenames(vertFilename, fragFilename);
    GLProgramState* glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);

    auto winsize = Director::getInstance()->getWinSizeInPixels();
    glprogramstate->setUniformVec2("cc_ViewSizeInPixels", winsize);
}
