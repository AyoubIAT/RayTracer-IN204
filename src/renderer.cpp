#include "renderer.hpp"



void render(int width, int height) {
    ofstream image("output.ppm");
    image << "P3\n" << width << " " << height << "\n255\n";
    
    Camera camera;

    Scene scene;

    // Create unique_ptr for spheres and add them to the scene
    std::unique_ptr<Parallelepiped> parallelepiped1 = std::make_unique<Parallelepiped>(Vector3d(0, 0.5, -4),Vector3d(2, 2.4, 2),Material(Color(0.1, 0.4, 0.8)));
    std::unique_ptr<Parallelepiped> parallelepiped2 = std::make_unique<Parallelepiped>(Vector3d(-1.75, 0.4, -4),Vector3d(1.5, 1.8, 2),Material(Color(0.9, 0.4, 0.2)));
    std::unique_ptr<Parallelepiped> parallelepiped3 = std::make_unique<Parallelepiped>(Vector3d(1.75, 0.3, -4),Vector3d(1.5, 0.8, 2),Material(Color(0.5, 0.7, 0.2)));
    std::unique_ptr<Sphere> sphere1 = std::make_unique<Sphere>(Vector3d(0, 2.2, -3), 0.5, Material(Color(0.1, 0.4, 0.8), 1));
    std::unique_ptr<Sphere> sphere2 = std::make_unique<Sphere>(Vector3d(-1.75, 1.7, -3), 0.5, Material(Color(0.9, 0.4, 0.2), 0.5));
    std::unique_ptr<Sphere> sphere3 = std::make_unique<Sphere>(Vector3d(1.75, 1.2, -3), 0.5, Material(Color(0.5, 0.7, 0.2)));
    std::unique_ptr<Sphere> sphere2a = std::make_unique<Sphere>(Vector3d(-2.6, 0.6, -2), 0.6, Material(Color(0.8, 0.2, 0.5)));
    std::unique_ptr<Sphere> sphere3a = std::make_unique<Sphere>(Vector3d(2.6, 0.3, -2), 0.3, Material(Color(0.1, 0.7, 0.8)));
    std::unique_ptr<Sphere> sphere3b = std::make_unique<Sphere>(Vector3d(3, 0.2, -3.5), 0.2, Material(Color(0.1, 0.4, 0.8)));
    std::unique_ptr<Sphere> sphere3c = std::make_unique<Sphere>(Vector3d(3.6, 0.8, -2.5), 0.8, Material(Color(0.8, 0.6, 0.1)));
    std::unique_ptr<Plane> ground = std::make_unique<Plane>(Material(Color(0.7, 0.7, 0.7), 0.2));

    scene.addObject(std::move(parallelepiped1));
    scene.addObject(std::move(parallelepiped2));
    scene.addObject(std::move(parallelepiped3));
    scene.addObject(std::move(sphere1));
    scene.addObject(std::move(sphere2));
    scene.addObject(std::move(sphere3));
    scene.addObject(std::move(sphere2a));
    scene.addObject(std::move(sphere3a));
    scene.addObject(std::move(sphere3b));
    scene.addObject(std::move(sphere3c));
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
