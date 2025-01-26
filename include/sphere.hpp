#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "ray.hpp"
#include <cmath>
#include <limits>
#include "material.hpp"

using Color = Eigen::Vector3d;

class Sphere : public Object {
public:
    Eigen::Vector3d center;
    float radius;
    Material material;
    
    Sphere(const Eigen::Vector3d& center, double radius, const Material& material);

    // Détection de l'intersection entre le rayon et la sphère
    std::optional<Intersection> intersect(const Ray& ray) const override;
};

#endif // SPHERE_HPP