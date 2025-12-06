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
				dielectric(vec3 albedo,double refractive_index):albedo(albedo),refractive_index(refractive_index){}
				bool scatter(const ray &incident, const HitRecord &rec, vec3 &attenuation, ray &scattered) override
				{
				attenuation = albedo;
				double ri = rec.facenorm?1.0/refractive_index:refractive_index;
				double cos_theta = -dot(incident.direction(),rec.norm);
						double sin_theta_2 = 1 - cos_theta*cos_theta;
				if(((ri>1) && (sin_theta_2*ri*ri>1) )||(reflectance(cos_theta,ri)>random_double_range(0, 1)))
						{
				vec3 reflected =reflect(incident.direction(),rec.norm);
				scattered = ray{rec.point,unit_vector(reflected)};
				return true;
						}
				vec3 refracted =refract(incident.direction(),rec.norm,ri);
				scattered = ray{rec.point,refracted};
				return true;
				}
				static double reflectance(double cosine, double refractive_index)
				{
						double r0= (1- refractive_index)/(1+refractive_index);
						r0=r0*r0;
						return r0 + (1-r0)*std::pow(1-cosine,5);

				}
private:
				vec3 albedo;
				double refractive_index;
};
