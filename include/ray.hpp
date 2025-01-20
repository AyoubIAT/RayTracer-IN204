#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <Eigen/Dense>

class Ray {
public:
    Eigen::Vector3d origin;
    Eigen::Vector3d direction;

    Ray() = default;
    Ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction)
        : origin(origin), direction(direction.normalized()) {}

    Eigen::Vector3d pointAtParameter(double t) const;

    void print() const;
};

#endif // RAY_HPP