#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <Eigen/Dense>

using namespace Eigen;
using Color = Vector3d;

class Material {
public:
    Color color; 

    Material(const Vector3d& color) : color(color) {}
};

#endif // MATERIAL_HPP