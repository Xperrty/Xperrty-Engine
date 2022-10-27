#pragma once
//#include "Core.h"
//#include "Application.h"
extern Xperrty::Application* Xperrty::createApplication();
int main(int argc, char** argv) {
    Xperrty::Log::Init();
    auto app = Xperrty::createApplication();
    app->run();
    XP_TRACE("XP_TRACE!{0}", 10);
    XP_INFO("XP_INFO!{0}", 11);
    XP_WARN("XP_WARN!{0}", 12);
    XP_ERROR("XP_ERROR{0}", 13);

   

    delete app;
}