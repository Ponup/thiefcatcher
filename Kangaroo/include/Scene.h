#pragma once

#include "EventHandler.h"

#include "GameObject.h"

#include "Renderer.h"

#include <vector>
#include <chrono>
using std::vector;

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::duration;

namespace Kangaroo {

    class Scene : public EventHandler {
    public:
        time_point<high_resolution_clock> initialTime;

        vector<Kangaroo::GameObject*> gameObjects;

        void init();
        void updateObjects();
        void renderObjects(Renderer& renderer);
    };
}