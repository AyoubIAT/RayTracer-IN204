#ifndef GROUND_HPP
#define GROUND_HPP

#include "object.hpp"
#include "ray.hpp"
#include <cmath>
#include <limits>
#include <Eigen/Dense>
#include "material.hpp"

using namespace Eigen;
using Color = Eigen::Vector3d;


class Plane : public Object {
public:
    Eigen::Vector3d point;
    Eigen::Vector3d normal;
    Material material;

    Plane();
    Plane(const Eigen::Vector3d& point, const Eigen::Vector3d& normal, const Material& material);
    Plane(const Material& material);


    // Détection d'intersection avec le sol
    std::optional<Intersection> intersect(const Ray& ray) const override;
};

#endif // GROUND_HPP