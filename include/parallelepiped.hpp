#ifndef PARALLELEPIPED_HPP
#define PARALLELEPIPED_HPP

#include "object.hpp"
#include "ray.hpp"
#include <cmath>
#include <limits>
#include "material.hpp"

using Color = Eigen::Vector3d;

class Parallelepiped : public Object {
public:
    Vector3d center; // Centre de gravité du parallélépipède rectangle
    Vector3d dimension; // x : longueur, y : largeur, z : hauteur
    Material material;
    
    Parallelepiped(const Vector3d& center, const Vector3d& dimension, const Material& material);

    // Détection d'intersection entre un rayon et le parallélépipède
    std::optional<Intersection> intersect(const Ray& ray) const override;
};

#endif // PARALLELEPIPED_HPP