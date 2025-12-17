#include "../lib/math/utilities.h"
#include "../lib/math/vec3.h"
#include "../renderer/camera.h"
#include "../renderer/material.h"
#include "../renderer/sphere.h"
#include "../renderer/plane.h"
#include "../renderer/mesh.h"
#include <memory>
#include <chrono>
/*TODO
 *
 * removing random vector and approaching uniform distribution
*/

int main() {
	auto start = std::chrono::steady_clock::now();
	HittableList world;
	std::shared_ptr<material> 	ground = std::make_shared<lambertian>(vec3{0.8,1.0,0.9}),
				   				plate = std::make_shared<lambertian>(vec3{0.1,1.0,0.5}),
				   				b1= std::make_shared<lambertian>(vec3{1.0,0.,0.}),
				   				b2= std::make_shared<metal>(vec3{1.0,0.,1.},0.0),
				   				b3= std::make_shared<dielectric>(vec3{1.0,1.,1.},1.5),
				   				b3b= std::make_shared<dielectric>(vec3{1.0,1.,1.},1/1.5);
	world.add(std::make_shared<Sphere>(vec3{0.0,0.0,-1.2},0.5,b1));	
	world.add(std::make_shared<Sphere>(vec3{1.0,.0,-1.0},0.5,b2));	
	world.add(std::make_shared<Sphere>(vec3{-1.0,0,-1.0},0.5,b3));	
	world.add(std::make_shared<Sphere>(vec3{-1.0,0,-1.0},0.4,b3b));	
	world.add(std::make_shared<Plane>(vec3{0.0,1,0.0},-0.5,ground));	
	//world.add(std::make_shared<Mesh>(vec3{.0,0.,0.0},.1,"../mesh/ImageToStl.com_21383_Inner_Triangles_v1/21383_Inner_Triangles_v1.stl",plate));	

	camera cam;
	cam.output_file="output.ppm";
	cam.aspect_ratio=16.0/9;
	cam.imageWidth=800;
	cam.vfov=20;
	cam.defocus_angle=0;
	cam.focal_dist=3.4;
	cam.lookfrom=vec3(-2.0,2.0,1.0)*2;
	cam.lookat=vec3(0.,0.,.0);
	cam.vup=vec3(0.,1.,0.0);
	cam.sample_count = 4;
	cam.max_depth = 7;
	cam.noOfThreads = 16;
	cam.initialize();
	cam.render(world);
	std::cout<<"Time taken "<<std::chrono::duration<double>(std::chrono::steady_clock::now()-start).count()<<"s"<<std::endl;
	
    return 0;
}
