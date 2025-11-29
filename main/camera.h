#pragma once
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "ray.h"
#include "hittable_list.h"
#include "material.h"
#include <fstream>
vec3 ray_color(const ray& r,HittableList& world,int max_depth = 2);

class camera
{
		public:
		double aspect_ratio=16.0/9;
		int image_width=400,image_height;
		double focal_length = 1.0;
		double viewport_height = 2.0;
		vec3 camera_center = vec3(0, 0, 0);
		int sample_count = 1;
		int max_depth = 25;
		private:
		vec3 pixel00_loc,//loc of (0,0) pixel at the top left
			 pixel_delta_u,pixel_delta_v;
		public:
		void render(const HittableList& world)
		{
		std::ofstream output("output/output.ppm");
		if(!output.is_open()){
				std::cout<<"Error in opening the file\n";
				exit(1);
		}

		output << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++) {
				for (int i = 0; i < image_width; i++){
						vec3 pixel_tl = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
						vec3 pixel_color = vec3(0.0);
						for(int u = 1; u<=sample_count;u++)
								for(int v = 1;v<=sample_count;v++)
								{
										vec3 ray_direction = pixel_tl+(u*pixel_delta_u+v*pixel_delta_v)/sample_count - camera_center;
						ray r(camera_center, ray_direction);
						vec3 col = ray_color(r,world,max_depth);
						pixel_color+=col;
								}
						pixel_color/=sample_count*sample_count;
						write(output,pixel_color);
				}
		}

		output.close();
		}

		void initialize()
		{	
		// Calculate the image height, and ensuring it's at least 1.
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;
		//resetting aspect_ratio from image_height and image_width
		aspect_ratio = image_width/double(image_height);

		// Camera
		double viewport_width = viewport_height * aspect_ratio;

		// Calculate the vectors across the horizontal and down the vertical viewport edges.
		vec3 viewport_u = vec3(viewport_width, 0, 0);
		vec3 viewport_v = vec3(0, -viewport_height, 0);

		// Calculate the horizontal and vertical delta vectors from pixel to pixel.
		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		// Calculate the location of the upper left pixel.
		vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
		pixel00_loc =viewport_upper_left;
		}
inline double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return sqrt(linear_component);

    return 0;
}
void write(std::ofstream& out, vec3 color){
		interval col(0,255);
        int ir = int(255 * linear_to_gamma(color[0]));
        int ig = int(255 * linear_to_gamma(color[1]));
        int ib = int(255 * linear_to_gamma(color[2]));
		if(!(col.contains(ir)&&col.contains(ig)&&col.contains(ib)))
		{
				std::cout<<"pixel is out of bound [0,255]\n"<<std::endl;
				exit(1);
		}
        out << ir << ' ' << ig << ' ' << ib << '\n';
}

vec3 ray_color(const ray& r,const HittableList& world,int depth) {
		if(depth<=0)return vec3(0.0);
		HitRecord rec;
		if(world.hit(r, interval(0.001, INFINITY), rec))
		{
				vec3 attenuation;ray scaterred;
				if(rec.mat->scatter(r,rec,attenuation,scaterred))
				{
						return attenuation*ray_color(scaterred,world,depth-1);
				}
				return vec3(0.0); 
		}
		vec3 unit_direction = unit_vector(r.direction());
		auto a = 0.5*(unit_direction.y() + 1.0);
		return (1.0-a)*vec3(1.0) + a*vec3(0.5, 0.7, 1.0);
}
};
