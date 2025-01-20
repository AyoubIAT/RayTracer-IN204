#include "renderer.hpp"


/*
    TODO:
        understand why there is no shadow : i'm only taking into account the dot product, so we don't know if there is an object that blocks light
        implement shadow

        cubes not just spheres

        understand how reflection works
        why need random vectors
        why need multiple, hundreds of, rays per pixel
        different type of materials

        create camera pov
        be able to move camera

        print pixels left to get an idea of execution time

        
*/

int main() {
    Camera camera;

    render(camera.width, camera.height);
    cout << "Image output.ppm générée." << endl;
    return 0;
}
