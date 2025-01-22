#include "renderer.hpp"


/*
    TODO:
        add cubes

        different types of materials

        create camera pov
        be able to move camera
        
*/

int main() {
    Camera camera;

    render(camera.width, camera.height);
    cout << "Image output.ppm générée." << endl;
    return 0;
}
