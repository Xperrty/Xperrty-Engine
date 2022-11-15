#pragma once
//#include "Core.h"
//#include "Application.h"
extern Xperrty::Application* Xperrty::createApplication();
int main(int argc, char** argv) {
    //ToDo:Fix all the casting issues.
    Xperrty::Log::Init();
    auto app = Xperrty::createApplication();
    app->run();
    delete app;
}