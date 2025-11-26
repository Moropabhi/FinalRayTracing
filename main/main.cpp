#include <iostream>
#include <fstream>
#include<cmath>
#include "vec3.h"
#include "ray.h"


void write(std::ofstream& out, vec3 color){

            int ir = int(255 * color[0]);
            int ig = int(255 * color[1]);
            int ib = int(255 * color[2]);

            out << ir << ' ' << ig << ' ' << ib << '\n';
}

vec3 hitsphere(vec3 center, float rad,const ray& r){
	float a, b, c;
	a=r.direction().length_squared();
	b=-2*dot(center - r.origin(),r.direction());
	c= (center - r.origin()).length_squared() - rad*rad;

	float D = b*b - 4*a*c;
	if (D<0){
	return vec3(0.5, 0.7, 1.0);
	}
	float t = (-b+std::sqrt(D))/2.0*a;
	vec3 N = unit_vector(r.at(t)-center);
        return 0.5*vec3(N.x()+1, N.y()+1, 1.);;
}
vec3 ray_color(const ray& r) {
    return hitsphere(vec3(0,0,-1),0.5,r);
}


int main() {
	// File
    std::ofstream output("output.ppm");
    // Image Properties
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 800;

    // Calculate the image height, and ensuring it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width)/image_height);
    vec3 camera_center = vec3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    vec3 viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
	//setting up ppm file
    output << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) 
    {
        for (int i = 0; i < image_width; i++) 
	{
vec3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            vec3 pixel_color = ray_color(r);
            write(output,pixel_color);
        }
    }

    output.close();
    return 0;
}
