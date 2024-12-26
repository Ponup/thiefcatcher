#include "Scene.h"

void Kangaroo::Scene::init() {
    initialTime = high_resolution_clock::now();
}

void Kangaroo::Scene::updateObjects() {
    duration<double> elapsedTime = high_resolution_clock::now() - initialTime;
    for (GameObject* go : gameObjects) {
        go->update(elapsedTime.count());
    }
}

void Kangaroo::Scene::renderObjects(Renderer& renderer) {
    for (GameObject* go : gameObjects) {
        go->render();
    }
}
