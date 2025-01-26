#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <Eigen/Dense>

using namespace Eigen;
using Color = Vector3d;

class Material {
public:
    Color color; 
    double reflectivity;         // 0 = no reflectivity; 1 = mirror; 0 < reflection+diffusion < 1
    double indice_refraction;    // 1.0 = air, 1.5 = glass, 2.42 = diamond (0 = no refraction)

    Material(const Vector3d& color) : color(color), reflectivity(0.0), indice_refraction(0.0) {}
    Material(const Vector3d& color, double reflectivity) : color(color), reflectivity(reflectivity), indice_refraction(0.0) {}
    Material(const Vector3d& color, double reflectivity, double indice_refraction) : color(color), reflectivity(reflectivity), indice_refraction(indice_refraction) {}
};

#endif // MATERIAL_HPP