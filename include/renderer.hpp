#ifndef RENDERER_HPP
#define RENDERER_HPP


#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include "ray.hpp"
#include "color.hpp"
#include "scene.hpp"
#include "material.hpp"
#include "camera.hpp"

using namespace Eigen;
using namespace std;

void render(int width, int height);


#endif