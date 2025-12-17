#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "hittable_list.h"

#include <memory>

class Rectangle : public HittableObject
{
		public:
		vec3 normal={0,0,-1};
		vec3 center = {0.0};
		double a=5,b = 5;
		std::shared_ptr<material> mat;
		Rectangle()=default;
		Rectangle(vec3 center,vec3 u,vec3 v, double a,double b,std::shared_ptr<material> mat):normal(cross(u,v)),center(center),a(a),b(b),u(unit_vector(u)),v(unit_vector(v)),mat(mat){
		c=dot(normal,center);

		}


		virtual bool hit (const ray& r,interval rayt,HitRecord& rec) const override
		{
				if(dot(normal,r.direction())==0)return false;
				double t = (c-dot(normal,r.origin()))/dot(normal,r.direction());
				vec3 temp = r.at(t);
				if(!rayt.contains(t) ||(std::abs(2*dot(u,temp-center))>a)||(std::abs(2*dot(v,temp-center))>b))
				{
						return false;
				}
				rec.setFaceNormal(r,normal);
				rec.point=temp;
				rec.t=t;
				rec.mat=mat;
				return true;	
		}
		std::shared_ptr<AABB> getAABB() const override
		{
				std::shared_ptr<AABB> v = std::make_shared<AABB>(this);
				v->a=minVec3(center+u/2*a+this->v/2*b,center-u/2*a-this->v/2*b);	
				v->b=maxVec3(center+u/2*a+this->v/2*b,center-u/2*a-this->v/2*b);	
				return v;
		}
		private:
		vec3 u,v;
		double c;
};
#endif
