#ifndef SCENE_H_
#define SCENE_H_

#include "entt.hpp"

namespace GL
{
    class Scene
    {
    public:
        Scene();
        ~Scene();
    private:
        entt::registry m_Registry;
    };
}

#endif //SCENE_H_