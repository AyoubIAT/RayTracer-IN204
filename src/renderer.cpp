#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
#include <atomic>
#include <sstream>
#include <iostream>
#include "renderer.hpp"

// Mutex for writing progress to the console
std::mutex progress_mutex;

// Shared container for ordered output
std::vector<std::string> image_rows;

// Atomic counter for progress
std::atomic<int> progress_counter(0);

void renderSlice(int start_row, int end_row, int width, int height, int num_samples, Camera& camera, Scene& scene) {
    for (int j = start_row; j < end_row; ++j) {
        std::stringstream row_buffer; // Buffer for the current row
        for (int i = 0; i < width; ++i) {
            Vector3i color = getPixelColor(i, j, num_samples, camera, scene);
            int ir = color.x();
            int ig = color.y();
            int ib = color.z();
            row_buffer << ir << " " << ig << " " << ib << "\n";
        }

        // Store the row in the correct position
        // Flip the index to store the rows from top to bottom in the final image
        image_rows[height - 1 - j] = row_buffer.str();

        // Update progress
        progress_counter++;
        if (progress_counter % (height / 20) == 0) { // Update progress for every 5% of rows rendered
            std::lock_guard<std::mutex> lock(progress_mutex);
            std::cout << "Progress: " << (100 * progress_counter / height) << "%\r" << std::flush;
        }
    }
}


void render(int width, int height) {
    std::ofstream image("output.ppm");
    image << "P3\n" << width << " " << height << "\n255\n";

    Camera camera;
    Scene scene;

    std::unique_ptr<Parallelepiped> parallelepiped1 = std::make_unique<Parallelepiped>(Vector3d(0, 0.5, -4),Vector3d(2, 2.4, 2),Material(Color(0.1, 0.4, 0.8)));
    std::unique_ptr<Parallelepiped> parallelepiped2 = std::make_unique<Parallelepiped>(Vector3d(-1.75, 0.4, -4),Vector3d(1.5, 1.8, 2),Material(Color(0.9, 0.4, 0.2)));
    std::unique_ptr<Parallelepiped> parallelepiped3 = std::make_unique<Parallelepiped>(Vector3d(1.75, 0.3, -4),Vector3d(1.5, 0.8, 2),Material(Color(0.5, 0.7, 0.2)));

    std::unique_ptr<Parallelepiped> parallelepiped_tapis = std::make_unique<Parallelepiped>(Vector3d(0, 0, 0),Vector3d(1.6, 0.01, 8),Material(Color(0.2, 0.9, 0.4)));

    std::unique_ptr<Sphere> sphere1 = std::make_unique<Sphere>(Vector3d(0, 2.2, -3.5), 0.5, Material(Color(0.1, 0.4, 0.8), 0.1, 1.5));
    std::unique_ptr<Sphere> sphere2 = std::make_unique<Sphere>(Vector3d(-1.75, 1.8, -3.5), 0.5, Material(Color(0.9, 0.4, 0.2), 0.5));
    std::unique_ptr<Sphere> sphere3 = std::make_unique<Sphere>(Vector3d(1.75, 1.2, -3.5), 0.5, Material(Color(0.5, 0.7, 0.2)));

    std::unique_ptr<Sphere> sphere2a = std::make_unique<Sphere>(Vector3d(-2.6, 0.6, -2), 0.6, Material(Color(0.8, 0.2, 0.5), 0.95));
    std::unique_ptr<Sphere> sphere2z = std::make_unique<Sphere>(Vector3d(-1, 0.25, -2.2), 0.25, Material(Color(0.8, 0.2, 0.5),0.1,1.2));
    std::unique_ptr<Sphere> sphere3a = std::make_unique<Sphere>(Vector3d(2.6, 0.3, -2), 0.3, Material(Color(0.1, 0.7, 0.8), 0.2));
    std::unique_ptr<Sphere> sphere3b = std::make_unique<Sphere>(Vector3d(3, 0.2, -3.5), 0.2, Material(Color(0.1, 0.4, 0.8), 0.1));
    std::unique_ptr<Sphere> sphere3c = std::make_unique<Sphere>(Vector3d(3.6, 0.8, -2.5), 0.8, Material(Color(0.8, 0.6, 0.1), 0.1));

    std::unique_ptr<Plane> ground = std::make_unique<Plane>(Material(Color(0.7, 0.7, 0.7), 0.2));

    scene.addObject(std::move(parallelepiped1));
    scene.addObject(std::move(parallelepiped2));
    scene.addObject(std::move(parallelepiped3));
    scene.addObject(std::move(parallelepiped_tapis));
    scene.addObject(std::move(sphere1));
    scene.addObject(std::move(sphere2));
    scene.addObject(std::move(sphere3));
    scene.addObject(std::move(sphere2a));
    scene.addObject(std::move(sphere2z));
    scene.addObject(std::move(sphere3a));
    scene.addObject(std::move(sphere3b));
    scene.addObject(std::move(sphere3c));
    scene.addObject(std::move(ground));


    int num_samples = 3; // Number of rays per pixel
    int num_threads = std::thread::hardware_concurrency(); // Number of threads
    int slice_height = height / num_threads; // Rows per thread

    // Resize the shared container to store image rows
    image_rows.resize(height);

    // Create threads
    std::vector<std::thread> threads;
    for (int t = 0; t < num_threads; ++t) {
        int start_row = t * slice_height;
        int end_row = (t == num_threads - 1) ? height : start_row + slice_height;
        threads.emplace_back(renderSlice, start_row, end_row, width, height, num_samples, std::ref(camera), std::ref(scene));
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Write the final image to the file
    for (const auto& row : image_rows) {
        image << row;
    }

    image.close();

    // Final progress update
    std::cout << "Progress: 100%" << std::endl;
}
