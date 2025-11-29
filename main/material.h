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
class dielectric:public material
{
		public:
				dielectric(vec3 albedo,double refractive_index,double probability_of_reflection):albedo(albedo),refractive_index(refractive_index),p_reflect(probability_of_reflection){}
				bool scatter(const ray &incident, const HitRecord &rec, vec3 &attenuation, ray &scattered) override
				{
				attenuation = albedo;
				if(p_reflect!=0)
				{
						if(random_double()<=p_reflect)
						{
						vec3 reflected =reflect(incident.direction(),rec.norm);
						scattered = ray{rec.point,unit_vector(reflected)};
						return true;
						}
				}
				double ri = rec.facenorm?1.0/refractive_index:refractive_index;
				double cos_theta = -dot(incident.direction(),rec.norm);
				if(ri>1)
				{
						double sin_theta_2 = 1 - cos_theta*cos_theta;
						if(sin_theta_2*ri*ri>1)
						{
				vec3 reflected =reflect(incident.direction(),rec.norm);
				scattered = ray{rec.point,unit_vector(reflected)};
				return true;
						}
				}
				vec3 refracted =refract(incident.direction(),rec.norm,ri);
				scattered = ray{rec.point,refracted};
				return true;
				}
private:
				vec3 albedo;
				double refractive_index;
				double p_reflect;
};
