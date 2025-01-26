#include "parallelepiped.hpp"


Parallelepiped::Parallelepiped(const Vector3d& center, const Vector3d& dimension, const Material& material)
    : center(center), dimension(dimension), material(material) {}


std::optional<Intersection> Parallelepiped::intersect(const Ray& ray) const {
    Eigen::Vector3d halfDim = dimension / 2.0; // Half-size along each axis
    Eigen::Vector3d minCorner = center - halfDim;
    Eigen::Vector3d maxCorner = center + halfDim;

    double tMin = -std::numeric_limits<double>::infinity();
    double tMax = std::numeric_limits<double>::infinity();

    for (int i = 0; i < 3; i++) { // Loop over x, y, and z
        if (ray.direction[i] != 0) { // Avoid division by zero
            double t1 = (minCorner[i] - ray.origin[i]) / ray.direction[i];
            double t2 = (maxCorner[i] - ray.origin[i]) / ray.direction[i];

            if (t1 > t2) std::swap(t1, t2);

            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);
        }
        else if (ray.origin[i] < minCorner[i] || ray.origin[i] > maxCorner[i]) {
            return std::nullopt;
        }
    }

    if (tMax < tMin || tMax < 0) {
        return std::nullopt; // No valid intersection
    }

    double t = (tMin > 0) ? tMin : tMax; // Choose nearest positive intersection
    Eigen::Vector3d point = ray.pointAtParameter(t);

    // Compute normal by checking which face was hit
    Eigen::Vector3d normal(0, 0, 0);
    for (int i = 0; i < 3; i++) {
        if (std::abs(point[i] - minCorner[i]) < 1e-6) normal[i] = -1;
        else if (std::abs(point[i] - maxCorner[i]) < 1e-6) normal[i] = 1;
    }

    return Intersection(t, point, normal, material);
}
