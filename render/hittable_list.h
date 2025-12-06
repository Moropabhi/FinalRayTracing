#pragma once
//#include "material.h"
#include "ray.h"
#include <memory>
#include <vector>
#include "../lib/math/interval.h"

class material;

struct HitRecord
{
vec3 point;
vec3 norm;
double t;
bool facenorm;
void setFaceNormal(const ray& r, vec3& n)
{
		facenorm=dot(r.direction(),n)<0;
		norm = facenorm?n:-n;
}
std::shared_ptr<material> mat;

};
struct HittableObject
{
		public:
		virtual ~HittableObject() = default;
		virtual bool hit(const ray& r,interval rayt,HitRecord& rec) const =0;
};


class HittableList:public HittableObject
{
		public:
		std::vector<std::shared_ptr<HittableObject>> objects;

		void add(std::shared_ptr<HittableObject> o)
		{
				objects.push_back(o);
		}
		void clear(){objects.clear();}
		virtual bool hit(const ray& r,interval rayt,HitRecord& rec) const override
		{
				bool hitAny=false;
				for(auto& o:objects)
				{
						if(o->hit(r, rayt, rec))
						{
								if(!rayt.surrounds(rec.t))continue;
								rayt.max=rec.t;
								hitAny=true;
						}

				}
				return hitAny;
		}
		
};
