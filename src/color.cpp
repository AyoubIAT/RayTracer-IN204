#include "color.hpp"

double randomDouble() {
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

double randomDoubleMinMax(double min = 0.0f, double max = 1.0f) {
    return min + (max - min) * (static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
}

Vector3d randomUnitVector() {
    double a = randomDoubleMinMax(0, 2 * M_PI);
    double z = randomDoubleMinMax(-1, 1);
    double r = std::sqrt(1 - z * z);
    return Vector3d(r * std::cos(a), r * std::sin(a), z);
}


// Fonction pour convertir une couleur en un format PPM
inline void writeColor(std::ostream& out, const Color& color) {
    // On s'assure que les valeurs de couleur sont dans l'intervalle [0, 1]
    out << static_cast<int>(255 * color.x()) << ' '
        << static_cast<int>(255 * color.y()) << ' '
        << static_cast<int>(255 * color.z()) << '\n';
}

Color rayColor(const Ray &ray, const Scene &scene, int max_rebond) {
    if (max_rebond <= 0) {
        return Color(0, 0, 0);
    }

    auto intersection = scene.trace(ray);

    if (intersection) {
        const Intersection &intersection2 = *intersection;

        Color color(0,0,0);

        // Ombres : Lancer un rayon vers la source de lumière
        Vector3d lightPosition(4, 4, -1); // Position d'une source de lumière
        Vector3d lightDirection = (lightPosition - intersection2.point).normalized();
        Ray shadowRay(intersection2.point + 0.001 * intersection2.normal, lightDirection);

        if (!scene.trace(shadowRay)) {
            // Lumière diffuse
            double diffuse = std::max(intersection2.normal.dot(lightDirection), 0.0);
            color += diffuse * intersection2.material.color;
        }

        // Matériaux diffusants : Rayon réfléchi aléaoire
        Vector3d randomDirection = intersection2.normal + randomUnitVector();
        Ray scatteredRay(intersection2.point + 0.001 * intersection2.normal, randomDirection);

        // Récursivité pour calculer la lumière indirecte
        color += 0.5 * rayColor(scatteredRay, scene, max_rebond - 1);

        return color;
    }
    return Color(0,0,0);


    // Direction de la lumière
    // Eigen::Vector3d lightDirection = Eigen::Vector3d(5, -10, 0).normalized();

    // if (intersection) {
    //     double diffuse = std::max(0.0, - intersection->normal.dot(lightDirection));
    //     return intersection->material.color * diffuse;
    // }


    // return Color(0,0,0);
}

Vector3i getPixelColor(int i, int j, int num_samples, const Camera& camera, const Scene& scene) {
    Color color(0,0,0);

    for (int k = 0; k < num_samples; k++) {
        double u = (double(i) + randomDouble()) / double(camera.width);
        double v = (double(j) + randomDouble()) / double(camera.height);
        Ray ray(camera.origin, camera.lower_left_corner + u * camera.horizontal + v * camera.vertical - camera.origin);
        color += rayColor(ray, scene, 5);
        }
    color = color / num_samples;

    int ir = static_cast<int>(255 * color.x());
    int ig = static_cast<int>(255 * color.y());
    int ib = static_cast<int>(255 * color.z());

    return Vector3i(ir, ig, ib);
}