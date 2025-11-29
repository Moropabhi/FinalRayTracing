#include "../lib/math/vec3.h"
#include "camera.h"
#include "sphere.h"



int main() {

		HittableList world;
	world.add(std::make_shared<Sphere>(vec3{0.0,0.0,-1.0},vec3{1.0,0.0,0.0},0.5));	
	world.add(std::make_shared<Sphere>(vec3{0.0,-100.5,-1.0},vec3{.1},100.0));	

	camera cam;
		cam.aspect_ratio=16.0/9;
		cam.image_width=800;
		cam.focal_length = 1.0;
		cam.viewport_height = 2.0;
		cam.camera_center = vec3(0, 0, 0);
		cam.sample_count = 5;
		cam.depth = 25;
	cam.initialize();
	cam.render(world);
    return 0;
}
