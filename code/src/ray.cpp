#include "ray.hpp"


Eigen::Vector3d Ray::pointAtParameter(double t) const {
    return origin + t * direction;
}