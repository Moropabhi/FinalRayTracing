#ifndef PLANE_H
#define PLANE_H
#include "hittable_list.h"
#include <memory>

class Plane : public HittableObject
{
		public:
		vec3 normal={0,0,-1};
		double c = 0.5;
		std::shared_ptr<material> mat;
		Plane()=default;
		Plane(vec3 normal, double c,std::shared_ptr<material> mat):normal(normal),c(c),mat(mat){}


		virtual bool hit (const ray& r,interval rayt,HitRecord& rec) const override
		{
				if(dot(normal,r.direction())==0)return false;
				double t = (c-dot(normal,r.origin()))/dot(normal,r.direction());
				if(!rayt.contains(t))
				{
						return false;
				}
				rec.setFaceNormal(r,normal);
				rec.point=r.at(t);
				rec.t=t;
				rec.mat=mat;
				return true;	
		}
		AABB getBoundedBox() const override
		{
			return {vec3(-infinity),vec3(infinity)};
		}
};
#endif
