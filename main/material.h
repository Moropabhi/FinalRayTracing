#pragma once

#include "hittable_list.h"
#include "ray.h"

class material
{
		public:
		~material()=default;
		virtual bool scatter(const ray& incident,const HitRecord& rec, vec3& attenuation, ray& scattered)
		{
				return false;
		}

};

class lambertian:public material
{
		public:
				lambertian(vec3 albedo):albedo(albedo){}
				bool scatter(const ray &incident, const HitRecord &rec, vec3 &attenuation, ray &scattered) override
				{
				vec3 randv = rec.norm+random_dir();
				if(randv.near_zero())randv=rec.norm;
				else randv.normalise();
				//if(dot(randv,rec.norm)<=0)randv*=-1;
				scattered = ray{rec.point,randv};
				attenuation = albedo;
				return true;
				}
private:
				vec3 albedo;
};

class metal:public material
{
		public:
				metal(vec3 albedo,double fuzz):albedo(albedo),fuzz(fuzz){}
				bool scatter(const ray &incident, const HitRecord &rec, vec3 &attenuation, ray &scattered) override
				{
				vec3 reflected =reflect(incident.direction(),rec.norm)+fuzz*random_dir();
				scattered = ray{rec.point,unit_vector(reflected)};
				attenuation = albedo;
				return true;
				}
private:
				vec3 albedo;
				double fuzz;
};
