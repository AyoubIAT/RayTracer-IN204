#ifndef COLOR_HPP
#define COLOR_HPP

#include <memory>
#include <Eigen/Dense>
#include "ray.hpp"
#include "sphere.hpp"
#include "ground.hpp"
#include "scene.hpp"
#include "camera.hpp"

using Color = Eigen::Vector3d;
using namespace Eigen;


inline void writeColor(std::ostream& out, const Color& color);

Color rayColor(const Ray &ray, const Scene &scene, int max_rebond);

Vector3i getPixelColor(int i, int j, int num_samples, const Camera& camera, const Scene& scene);


#endif // COLOR_HPP