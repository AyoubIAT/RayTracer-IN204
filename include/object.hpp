#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <Eigen/Dense>
#include <memory>
#include <optional>
#include "material.hpp"

using Color = Eigen::Vector3d;
using Shape = std::string;

class Ray;

struct Intersection {
    double t;                            // t où l'intersection se produit
    Eigen::Vector3d point;               // Point d'intersection
    Eigen::Vector3d normal;              // Normale à l'objet au point d'intersection
    Material material;                         // Couleur de l'objet de l'intersection

    Intersection(double t, const Eigen::Vector3d& point, const Eigen::Vector3d& normal, const Material& material)
        : t(t), point(point), normal(normal), material(material) {}
    
};


class Object {
public:
    virtual ~Object() = default;

    // Méthode virtuelle pour calculer les intersections
    virtual std::optional<Intersection> intersect(const Ray& ray) const = 0;
};


#endif // OBJECT_HPP