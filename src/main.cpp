#include "renderer.hpp"




int main() {
    Camera camera;

    render(camera.width, camera.height);
    cout << "Image output.ppm générée." << endl;
    return 0;
}
