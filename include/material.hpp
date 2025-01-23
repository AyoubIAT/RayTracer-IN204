#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <Eigen/Dense>

using namespace Eigen;
using Color = Vector3d;

class Material {
public:
    Color color; 
    double reflectivity;

    // Material(const Vector3d& color) : color(color) {}
    Material(const Vector3d& color) : color(color), reflectivity(0.0) {}
    Material(const Vector3d& color, double reflectivity) : color(color), reflectivity(reflectivity) {}
};

#endif // MATERIAL_HPP