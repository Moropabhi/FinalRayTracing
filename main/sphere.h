#pragma  once
#include "hittable_list.h"

class Sphere : public HittableObject
{
		public:
		vec3 center={0,0,-1},color= {1.0};
		double rad = 0.5;
		Sphere()=default;
		Sphere(vec3 center, vec3 color, double rad):center(center),color(color),rad(rad){}


		virtual bool hit (const ray& r,interval rayt,HitRecord& rec)
		{
	double a, b, c;
	center-=r.origin();
	a=r.direction().length_squared();
	b=-2*dot(center,r.direction());
	c= center.length_squared() - rad*rad;
		center+=r.origin();
	double D = b*b - 4*a*c;
	if (D<0) return false;
	double t = (-b-std::sqrt(D))/2.0/a;

	if(!rayt.contains(t))
	{
		t = (-b+std::sqrt(D))/2.0/a;
		if(!rayt.contains(t))
		return false;
	}


	vec3 N = (r.at(t)-center)/rad;
//	vec3 Dir = unit_vector(vec3(1,-2,-0.5));
	rec.color=color;
	rec.setFaceNormal(r,N);
	rec.point=r.at(t);
	rec.t=t;
			return true;	
		}
};
