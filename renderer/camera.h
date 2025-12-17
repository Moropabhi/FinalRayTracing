#ifndef CAMERA_H
#define CAMERA_H
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "ray.h"
#include "hittable_list.h"
#include "material.h"
#include <fstream>
#include <string>
#include <vector>
#include <thread>
vec3 ray_color(const ray& r,HittableList& world,int max_depth = 2);

class camera
{
		public:
		double aspect_ratio=16.0/9;
		int imageWidth=400;
		int sample_count = 1;
		int max_depth = 25;
		float vfov;
		vec3 lookat,lookfrom,vup;
		float defocus_angle = 0;
		float focal_dist = 1.0;
		std::string output_file = "";
		int noOfThreads = 16;
		//vup is aligned along the height of the viewport 
		private:
		int imageHeight;
		double viewport_height = 2.0;
		vec3 camera_center = vec3(0, 0, 0);
		vec3 pixel_0_0,//loc of (0,0) pixel at the top left
			 pixelDelta_u,pixelDelta_v;
		float aperature_rad = 0;
		std::vector<vec3> data;
		vec3 u,v,w;
		public:
		void render(const HittableList& world)
		{
		std::vector<std::thread> vt;
		int nPixel = imageHeight*imageWidth;
		data = std::vector<vec3>(nPixel);
		vt.reserve(noOfThreads);
		for(int i = 0; i<noOfThreads;i++)
			vt.push_back(std::thread(genPixels,this,nPixel*i/noOfThreads, nPixel*(i+1)/noOfThreads, world));
		
		for(auto& t:vt)
			t.join();
		writeImage();
		}

		static void genPixels(camera* cam,int start,int end, const HittableList& world)
		{
		for(int i = start; i<end;i++)
		{
				vec3 pixel_tl = cam->pixel_0_0 + (i%cam->imageWidth * cam->pixelDelta_u) + (i/cam->imageWidth * cam->pixelDelta_v);
				cam->data[i] = cam->getPixel(world,pixel_tl);
		}

		}

		vec3 getPixel(const HittableList& world,vec3 pixel_tl)
		{
			vec3 pixel_color = vec3(0.0);
			for(int u = 1; u<=sample_count;u++)
				for(int v = 1;v<=sample_count;v++)
				{
					vec3 origin = (aperature_rad==0)?
						camera_center
						:camera_center+rand_unit_disk(u,v)*aperature_rad;
					vec3 ray_direction = pixel_tl+(u*pixelDelta_u+v*pixelDelta_v)/sample_count 
										- origin;
					ray_direction.normalise();
					ray r(origin, ray_direction);
					vec3 col = ray_color(r,world,max_depth);
					pixel_color+=col;
				}
			pixel_color/=sample_count*sample_count;
			return pixel_color;
		}

		void writeImage() const
		{
		std::ofstream output(output_file);
		if(!output.is_open()){
				std::cout<<"Error in opening the file\n";
				exit(1);
		}
		output << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
		for(auto& col:data)	
			write(output,col);
		output.close();
		}

		void initialize()
		{	
		// Calculate the image height, and ensuring it's at least 1.
		imageHeight = int(imageWidth / aspect_ratio);
		imageHeight = (imageHeight < 1) ? 1 : imageHeight;
		//resetting aspect_ratio from imageHeight and imageWidth
		aspect_ratio = imageWidth/double(imageHeight);

		// Camera
		camera_center=lookfrom;
		//up.normalise();
		w = lookat - lookfrom;
		w.normalise();
		w=-w;
		u=cross(vup,w);
		u.normalise();
		v=cross(w,u);
		viewport_height = 2*std::tan(degtorad( vfov/2))*focal_dist;
		double viewport_width = viewport_height * aspect_ratio;
		
		aperature_rad = std::tan(degtorad(defocus_angle/2))*focal_dist;

		// Calculate the vectors across the horizontal and down the vertical viewport edges.
		vec3 viewport_u = viewport_width*u;
		vec3 viewport_v = -viewport_height*v;

		// Calculate the horizontal and vertical delta vectors from pixel to pixel.
		pixelDelta_u = viewport_u / imageWidth;
		pixelDelta_v = viewport_v / imageHeight;

		// Calculate the location of the upper left pixel.
		vec3 viewport_upper_left = camera_center -focal_dist*w - viewport_u/2 - viewport_v/2;
		pixel_0_0 =viewport_upper_left;
		}
inline double linear_to_gamma(const double linear_component) const
{
    if (linear_component > 0)
        return sqrt(linear_component);

    return 0;
}
void write(std::ofstream& out, vec3 color) const
{
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
		if(depth<=0)return vec3(1.0,1.0,1.0);
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
#endif
