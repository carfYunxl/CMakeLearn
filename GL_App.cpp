#ifndef GL_EDITOR_H_
#define GL_EDITOR_H_

#include "App.h"
#include "src/LayerStack.h"
#include "GL_EditorLayer.h"

namespace GL
{
    class GLEditor: public App{
    public:
        GLEditor()
            :App("GL Editor")
        {
            PushLayer(new GL_EditorLayer());
        }
        ~GLEditor(){}
    private:
    };
}

int main()
{
    auto app = new GL::GLEditor();

    app->Run();

    delete app;

    return 0;
}

#endif //GL_EDITOR_H_