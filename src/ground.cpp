#include "ground.hpp"

Plane::Plane() : point(Vector3d(0,0,0)), normal(Vector3d(0,1,0)), material(Vector3d(0.5, 0.5, 0.5)) {}

Plane::Plane(const Eigen::Vector3d& point, const Eigen::Vector3d& normal,const Material& material)
        : point(point), normal(normal.normalized()), material(material) {}


Plane::Plane(const Material& material)
        : point(Vector3d(0,0,0)), normal(Vector3d(0,1,0)), material(material) {}


std::optional<Intersection> Plane::intersect(const Ray& ray) const {
    double denom = normal.dot(ray.direction);

    // Si le denominateur est égal à 0, rayon horizontal
    // if (std::abs(denom) < 1e-6) {
    //     return std::nullopt;
    // }

    double t = (point - ray.origin).dot(normal) / denom;

    if (t > 0) {
        Intersection inter(
            t,
            ray.pointAtParameter(t),
            normal,
            material);

        return inter;
    }

    return std::nullopt;
}
