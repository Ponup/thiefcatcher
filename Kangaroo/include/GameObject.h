#pragma once

#include "Renderer.h"

namespace Kangaroo {

    class GameObject {
    protected:
        Renderer renderer;

        GameObject() : renderer(nullptr) {
        }

    public:

        GameObject(Renderer& renderer) : renderer(renderer) {
        }

        virtual void update(double time) {
        	(void)time;
        }

        virtual void render() {
        }
    };
}
