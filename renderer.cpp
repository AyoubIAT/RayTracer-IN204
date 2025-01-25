#include "renderer.hpp"



void render(int width, int height) {
    ofstream image("output.ppm");
    image << "P3\n" << width << " " << height << "\n255\n";
    
    Camera camera;

    Scene scene;

    // Create unique_ptr for spheres and add them to the scene

    std::unique_ptr<Parallelepiped> parallelepiped1 = std::make_unique<Parallelepiped>(Vector3d(0, 0.5, -3),Vector3d(2, 2.5, 2),Material(Color(0.1, 0.4, 0.8)));
    std::unique_ptr<Parallelepiped> parallelepiped2 = std::make_unique<Parallelepiped>(Vector3d(-1.75, 0.4, -3),Vector3d(1.5, 1.8, 2),Material(Color(0.9, 0.4, 0.2)));
    std::unique_ptr<Parallelepiped> parallelepiped3 = std::make_unique<Parallelepiped>(Vector3d(1.75, 0.3, -3),Vector3d(1.5, 0.8, 2),Material(Color(0.5, 0.7, 0.2)));
    std::unique_ptr<Plane> ground = std::make_unique<Plane>(Material(Color(0.7, 0.7, 0.7), 0.2));

    scene.addObject(std::move(parallelepiped1));
    scene.addObject(std::move(parallelepiped2));
    scene.addObject(std::move(parallelepiped3));
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