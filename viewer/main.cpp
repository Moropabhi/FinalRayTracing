#include "../lib/math/vec3.h"
#include "../render/camera.h"
#include "../render/material.h"
#include "../render/sphere.h"
#include <fstream>
#include <istream>
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
				   b3= std::make_shared<dielectric>(vec3{1.0,1.,1.},1.5),
				   b3b= std::make_shared<dielectric>(vec3{1.0,1.,1.},1/1.5);
	world.add(std::make_shared<Sphere>(vec3{0.0,0.0,-1.2},0.5,b1));	
	world.add(std::make_shared<Sphere>(vec3{1.0,.0,-1.0},0.5,b2));	
	world.add(std::make_shared<Sphere>(vec3{-1.0,0,-1.0},0.5,b3));	
	world.add(std::make_shared<Sphere>(vec3{-1.0,0,-1.0},0.4,b3b));	
	world.add(std::make_shared<Sphere>(vec3{0.0,-100.5,-1.0},100.0,ground));	
	camera cam;
		std::ifstream in("viewer/transfer.txt");
		if(!in.is_open()){
				std::cout<<"Error in opening the file\n";
				exit(1);
		}
		in>>cam.aspect_ratio;
		in>>cam.image_width;
		in>>cam.vfov;
		in>>cam.defocus_angle;
		in>>cam.focal_dist;
		in>>cam.lookfrom[0];
		in>>cam.lookfrom[1];
		in>>cam.lookfrom[2];
		in>>cam.lookat[0];
		in>>cam.lookat[1];
		in>>cam.lookat[2];
		in>>cam.vup[0];
		in>>cam.vup[1];
		in>>cam.vup[2];
		in>>cam.sample_count;
		in>>cam.max_depth;
		in.close();
	cam.initialize();
	cam.render(world);
    return 0;
}
