#include "renderer.hpp"



void render(int width, int height) {
    ofstream image("output.ppm");
    image << "P3\n" << width << " " << height << "\n255\n";
    
    Camera camera;

    Scene scene;

    // Create unique_ptr for spheres and add them to the scene
    std::unique_ptr<Sphere> sphere1 = std::make_unique<Sphere>(Vector3d(0, 1, -3), 1, Material(Color(0.5,0.7,0.2)));
    std::unique_ptr<Sphere> sphere2 = std::make_unique<Sphere>(Vector3d(1.5, 1, -2), 1, Material(Color(0.1,0.4,0.8)));
    std::unique_ptr<Parallelepiped> parallelepiped = std::make_unique<Parallelepiped>(Vector3d(-1.5, 4, -8), Vector3d(1, 8, 1), Material(Color(0.9,0.4,0.2)));
    std::unique_ptr<Plane> ground = std::make_unique<Plane>();

    scene.addObject(std::move(sphere1));
    scene.addObject(std::move(sphere2));
    scene.addObject(std::move(parallelepiped));
    scene.addObject(std::move(ground));

    // Nombre de rayon lancés par pixel
    int num_samples = 10;

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            std::cout << "Progression : " << 100 * (width * (height-1-j) + i)/(width*height) << "%" << std::endl;
            Vector3i color = getPixelColor(i, j, num_samples, camera, scene);
            int ir = color.x();
            int ig = color.y();
            int ib = color.z();
            image << ir << " " << ig << " " << ib << "\n";
        }
    }
    image.close();
}