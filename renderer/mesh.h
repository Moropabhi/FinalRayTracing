#ifndef MESH_H
#define MESH_H
#include "hittable_list.h"
#include "triangle.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "bvh_node.h"
using tri = struct tri
{
		float_t norm[3];
		float_t a[3][3];
		uint16_t count;
};
class Mesh: public HittableObject
{
		public:
		std::vector<std::shared_ptr<HittableObject>> data;
		std::shared_ptr<material> mat;
		Mesh()=default;
		vec3 origin;
		float scale;
		interval r[3];
		Mesh(vec3 origin,float scale,std::string filename,std::shared_ptr<material> mat)
:origin(origin), mat(mat), scale(scale)
		{
				load(filename);
				vol=BVH(data,0,data.size());
				aabb=vol.getBoundedBox();
		}

		Mesh& load(std::string filename)
		{
				auto s = filename.substr(filename.size()-4);
				if(s==".stl")
						loadSTL(filename);
				else std::cout<<"MeshLoad:\""<<filename<<"\" is not loaded as this \""<<s<<"\" is not supported.\n";
				
				return *this;
		}


		virtual bool hit (const ray& ry,interval rayt,HitRecord& rec) const override
		{
			return vol.hit(ry,rayt,rec);
			bool hitAny = false;
			for(auto& o:data)
			{
				if(o->hit(ry, rayt, rec))
					{
						hitAny=true;
						rayt.max=rec.t;
					}
			}
			return hitAny;//*/
		}
		AABB getBoundedBox() const override
		{
			return aabb;
		}
		private:
		void loadSTL(std::string filename)
		{
				std::ifstream in(filename,std::ios_base::binary|std::ios_base::in);
				if(!in.is_open())
				{
						std::cout<<"Cannot open the file\n";
						exit(1);
				}
				{
				char s[5];
				in.read(s,5);
				if(strcmp(s,"solid")==0)std::cout<<"OhNo\n";
				}
				{
				char s[75];
				in.read(s,75);
				}
				unsigned int n;
				in.read((char*)&n,4);
				data.reserve(n);
				std::cout<<n<<std::endl;
				tri temp;
				for(int i = 0;i<n;i++)
				{
						in.read((char*)&temp,50);
						for(int i = 0; i<3;i++)
								for(int j = 0; j<3;j++)
										r[i].update(temp.a[j][i]);
						data.push_back(std::make_shared<Triangle>(vec3{temp.norm},vec3{temp.a[0]}*scale+origin,vec3{temp.a[1]}*scale+origin,vec3{temp.a[2]}*scale+origin,mat));
				}
				in.close();
				std::sort(data.begin(),data.end(),[](std::shared_ptr<HittableObject>v1,std::shared_ptr<HittableObject>v2){
	auto a = v1->getBoundedBox();auto b = v2->getBoundedBox();
	for(int i =0;i<3;i++){
	if(a.min[i]<b.min[i])return true;
	if(a.min[i]>b.min[i])return false;
	}
	return true;});
		}
		AABB aabb;
		BVH vol;
};
#endif
