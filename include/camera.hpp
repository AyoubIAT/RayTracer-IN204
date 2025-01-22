#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Eigen/Dense>

using namespace Eigen;
using Color = Vector3d;

class Camera {
public:
    int width = 1000;
    int height = width/2;

    Vector3d lower_left_corner;
    Vector3d horizontal;
    Vector3d vertical;
    Vector3d origin;



    Camera()
        : lower_left_corner(-2.0, 0, -1.0),
          horizontal(4.0, 0.0, 0.0),
          vertical(0.0, 2.0, 0.0),
          origin(0.0, 1.0, 0.0) {}

};

#endif // CAMERA_HPP