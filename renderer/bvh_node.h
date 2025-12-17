#ifndef BVH_NODE_H
#define BVH_NODE_H
#include "hittable_list.h"
#include <memory>
#include <vector>
//Bounding Volume hierachies
class BVH:public HittableObject
{
	public:
		BVH(){}
	BVH(std::vector<std::shared_ptr<HittableObject>>& v,int start,int n)
	{
		if(n==1)
		{
			left=v[start];
			right=v[start];
		}else if(n==2)
		{
			left = v[start+1];
			right = v[start];
		}else
		{
			left = std::make_shared<BVH>(v,start,n/2);
			right = std::make_shared<BVH>(v,start+n/2,n-n/2);
		}
		box = AABB(left->getBoundedBox(),right->getBoundedBox());
	}

	bool hit(const ray &r, interval rayt, HitRecord &rec) const override
	{
		if(!box.hit(r, rayt)){return false;}
		bool hitAny= left->hit(r, rayt, rec);
		if(hitAny)rayt.max = rec.t;
		auto hitAny2 =right->hit(r, rayt, rec);
		return hitAny||hitAny2;
	}
	AABB getBoundedBox() const override
	{
		return box;
	}
	private:
	AABB box;
	std::shared_ptr<HittableObject> left,right;
};
#endif
