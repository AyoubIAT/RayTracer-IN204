#include "sphere.hpp"


Sphere::Sphere(const Eigen::Vector3d& center, double radius,const Material& material)
    : center(center), radius(radius), material(material) {}


std::optional<Intersection> Sphere::intersect(const Ray& ray) const {
    Eigen::Vector3d oc = center - ray.origin;
    double a = ray.direction.dot(ray.direction);
    double b = - 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double t = (-b - std::sqrt(discriminant)) / (2.0 * a);
        if (t > 0) {
            Vector3d point = ray.pointAtParameter(t);
            Intersection inter(
                t,
                point,
                (point - center).normalized(),
                material);

            return inter; 
        }
    }
    return std::nullopt;
}