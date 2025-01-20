#include "color.hpp"

// Fonction pour convertir une couleur en un format PPM
inline void writeColor(std::ostream& out, const Color& color) {
    // On s'assure que les valeurs de couleur sont dans l'intervalle [0, 1]
    out << static_cast<int>(255.999 * color.x()) << ' '
        << static_cast<int>(255.999 * color.y()) << ' '
        << static_cast<int>(255.999 * color.z()) << '\n';
}

Color rayColor(const Ray &ray, const Scene &scene) {
    auto intersection = scene.trace(ray);

    // Direction de la lumière
    Eigen::Vector3d lightDirection = Eigen::Vector3d(5, -10, 0).normalized();

    if (intersection) {
        double diffuse = std::max(0.0, - intersection->normal.dot(lightDirection));
        return intersection->material.color * diffuse;
    }

    // if (intersection) {
    //     return intersection->material.color;
    // }

    return Color(0,0,0);

}