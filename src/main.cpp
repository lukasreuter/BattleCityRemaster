#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include <Magnum/GL/Context.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Color.h>

#include <iostream>
#include <entt.hpp>

using namespace Magnum;

class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    private:
        void drawEvent() override;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::Application{arguments} {
    /* TODO: Add your initialization code here */
    
    using namespace Magnum::Math::Literals;
    
    GL::Renderer::setClearColor(0xa5c9ea_rgbf);
    
    Debug{} << "Hello! This application is running on"
        << GL::Context::current().version() << "using"
        << GL::Context::current().rendererString();
}

void MyApplication::drawEvent() {
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

    //std::cout << "Halp" << std::endl;
    /* TODO: Add your drawing code here */

    swapBuffers();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
