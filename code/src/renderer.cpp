#include "renderer.hpp"

void render(int width, int height) {
    ofstream image("output.ppm");
    image << "P3\n" << width << " " << height << "\n255\n";
    
    Vector3d lower_left_corner(-2.0, 0, -1.0);
    Vector3d horizontal(4.0, 0.0, 0.0);
    Vector3d vertical(0.0, 2.0, 0.0);
    Vector3d origin(0.0, 1.0, 0.0);

    Scene scene;

    // Create unique_ptr for spheres and add them to the scene
    std::unique_ptr<Sphere> sphere1 = std::make_unique<Sphere>(Vector3d(0, 1, -3), 1, Material(Color(0.5,0.7,0.2)));
    std::unique_ptr<Sphere> sphere2 = std::make_unique<Sphere>(Vector3d(1.5, 1, -2), 1, Material(Color(0.1,0.4,0.8)));
    std::unique_ptr<Plane> ground = std::make_unique<Plane>();

    scene.addObject(std::move(sphere1));
    scene.addObject(std::move(sphere2));
    scene.addObject(std::move(ground));

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            double u = double(i) / double(width);
            double v = double(j) / double(height);
            Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            Color color = rayColor(ray, scene);
            int ir = static_cast<int>(255 * color.x());
            int ig = static_cast<int>(255 * color.y());
            int ib = static_cast<int>(255 * color.z());
            image << ir << " " << ig << " " << ib << "\n";
        }
    }
    image.close();
}