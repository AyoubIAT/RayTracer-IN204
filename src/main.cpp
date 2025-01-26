#include "renderer.hpp"


/*
    TODO:
        improve camera fov
        be able to move camera
*/

int main() {
    Camera camera;

    render(camera.width, camera.height);
    cout << "Image output.ppm générée." << endl;
    return 0;
}
