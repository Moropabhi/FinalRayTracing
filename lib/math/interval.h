#ifndef INTERVAL_H
#define INTERVAL_H
#include "utilities.h"
class interval {
  public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }
void update(double x)
{
		if(x>max)max=x;
		if(x<min)min=x;
}
static interval intersect(interval t1,interval t2)
{
		interval t;
		t.max=t1.max>t2.max?t2.max:t1.max;
		t.min=t1.min<t2.min?t2.min:t1.min;
		return t;
}
bool is_empty() const
{
		return min>=max;
}
    static const interval empty, universe;
};
const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
#endif

