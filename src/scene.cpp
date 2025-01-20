#include "scene.hpp"

void Scene::addObject(std::unique_ptr<Object> object) {
    objects.push_back(std::move(object));
}

std::optional<Intersection> Scene::trace(const Ray& ray) const {
    std::optional<Intersection> closestIntersection;
    double closestT = std::numeric_limits<double>::max(); // + l'infini

    for (const auto& object : objects) {
        auto intersection = object->intersect(ray);
        // Si il y a une intersection et que cette intersection à lieu avant l'intersection déjà stockée.
        if (intersection && intersection->t < closestT) {
            closestT = intersection->t;
            closestIntersection = intersection;
        }
    }

    return closestIntersection;
}