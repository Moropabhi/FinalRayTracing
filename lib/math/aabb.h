#ifndef AABB_H
#define AABB_H
#include "vec3.h"
#include <memory>
#include <vector>
#include "interval.h"
#include "../../renderer/ray.h"


struct AABB
{
	AABB(){}
	AABB(vec3 a,vec3 b):min(a),max(b){}
	AABB(AABB a,AABB b)
	:min(minVec3(a.min,b.min)),max(maxVec3(a.max, b.max))
	{}

	bool hit(const ray &r, interval rayt) const
	{	
		vec3 a = (min-r.origin())/r.direction(),b=(max-r.origin())/r.direction();
		for(int i = 0; i<3;i++)
			if(a[i]>b[i]){auto x = a[i];a[i]=b[i];b[i]=x;}
		auto t1 = fmax(a[0],fmax(a[1],a[2])),t2 = fmin(b[0],fmin(b[1],b[2]));

		return t1<=t2&&(t1<rayt.max&&t2>rayt.min);
	}
	vec3 min,max;
};
#endif
