#include "../lib/math/vec3.h"
#include "camera.h"
#include "material.h"
#include "sphere.h"
#include <memory>
/*TODO
 *
 * removing random vector and approaching uniform distribution
*/

int main() {

		HittableList world;
		std::shared_ptr<material> ground = std::make_shared<lambertian>(vec3{0.8,1.0,0.9}),
				   b1= std::make_shared<lambertian>(vec3{1.0,0.,0.}),
				   b2= std::make_shared<metal>(vec3{1.0,0.,1.},0.0),
				   b3= std::make_shared<metal>(vec3{1.0,1.,0.},0.5);
	world.add(std::make_shared<Sphere>(vec3{0.0,0.0,-1.0},0.5,b1));	
	world.add(std::make_shared<Sphere>(vec3{1.5,.0,-1.0},0.5,b2));	
	world.add(std::make_shared<Sphere>(vec3{-1.5,0,-1.0},0.5,b3));	
	world.add(std::make_shared<Sphere>(vec3{0.0,-100.5,-1.0},100.0,ground));	

	camera cam;
		cam.aspect_ratio=16.0/9;
		cam.image_width=800;
		cam.focal_length = 1.0;
		cam.viewport_height = 4.0;
		cam.camera_center = vec3(0, 0, 0);
		cam.sample_count = 10;
		cam.max_depth = 50;
	cam.initialize();
	cam.render(world);
    return 0;
}
