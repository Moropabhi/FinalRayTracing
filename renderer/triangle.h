#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "hittable_list.h"
#include <memory>

class Triangle: public HittableObject
{
		public:
		vec3 normal={0,0,-1};
		vec3 A,B,C;
		std::shared_ptr<material> mat;
		Triangle()=default;
		Triangle(vec3 A,vec3 B,vec3 C,std::shared_ptr<material> mat)
			:Triangle(cross(A-B,B-C),A,B,C,mat)
		{}
		Triangle(vec3 norm,vec3 A,vec3 B,vec3 C,std::shared_ptr<material> mat):normal(norm),A(A),B(B),C(C),a(B-C),b(A-C),c(A-B),mat(mat){
				c0=dot(normal,C);
				a=cross(normal,a);
				b=cross(normal,b);
				c=cross(normal,c);
				c1 = dot(a,B-A);
				if(c1<0){c1=-c1;a=-a;}
				c2 = dot(b,C-B);
				if(c2<0){c2=-c2;b=-b;}
				c3 = dot(c,A-C);
				if(c3<0){c3=-c3;c=-c;}
				aabb=AABB(minVec3(A, minVec3(B, C)),maxVec3(A, maxVec3(B, C)));
		}


		virtual bool hit (const ray& r,interval rayt,HitRecord& rec) const override
		{
				if(dot(normal,r.direction())==0)return false;
				double t = (c0-dot(normal,r.origin()))/dot(normal,r.direction());
				if(!rayt.contains(t))
						return false;
				vec3 temp = r.at(t);
				double d1 = dot(a,temp-A),
				d2 = dot(b,temp-B),
				d3 = dot(c,temp-C);
				if((d1>c1)||(d2>c2)||(d3>c3))
				{
						return false;
				}
				rec.setFaceNormal(r,normal);
				rec.point=temp;
				rec.t=t;
				rec.mat=mat;
				return true;	
		}
		AABB getBoundedBox() const override
		{
			return aabb;
		}
		private:
		vec3 a,b,c;
		double c0;
		double c1,c2,c3;
		AABB aabb;
};
#endif
