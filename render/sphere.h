#pragma  once
#include "hittable_list.h"
#include <memory>

class Sphere : public HittableObject
{
		public:
		vec3 center={0,0,-1};
		double rad = 0.5;
		std::shared_ptr<material> mat;
		Sphere()=default;
		Sphere(vec3 center, double rad,std::shared_ptr<material> mat):center(center),rad(rad),mat(mat){}


		virtual bool hit (const ray& r,interval rayt,HitRecord& rec)const override
		{
	double a, b, c;
	vec3 cr= center - r.origin();
	a=r.direction().length_squared();
	b=-2*dot(cr,r.direction());
	c= cr.length_squared() - rad*rad;
		//center+=r.origin();
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
	rec.setFaceNormal(r,N);
	rec.point=r.at(t);
	rec.t=t;
	rec.mat=mat;
			return true;	
		}
};
