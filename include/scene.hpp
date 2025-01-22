#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include "object.hpp"
#include "ray.hpp"

class Scene {
public:
    // Liste des objets présents dans la scène
    std::vector<std::unique_ptr<Object>> objects;

    // Ajouter un objet à la scène
    void addObject(std::unique_ptr<Object> object);

    // Lancer un rayon et trouver l'objet d'intersection le plus proche
    std::optional<Intersection> trace(const Ray& ray) const;
};

#endif // SCENE_HPP