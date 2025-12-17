#ifndef VEC3_H
#define VEC3_H

#include "./utilities.h"

class vec3 {
  private:
    double e[3];
public:
    vec3() : e{0,0,0} {}
    vec3(double x) : e{x,x,x} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
    vec3(double v[3]) : e{v[0], v[1], v[2]} {}
    vec3(float v[3]) : e{v[0], v[1], v[2]} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    double& x() { return e[0]; }
    double& y() { return e[1]; }
    double& z(){ return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
        e[0] += v[0];
        e[1] += v[1];
        e[2] += v[2];
        return *this;
    }
    vec3& operator-=(const vec3& v) {
        e[0] -= v[0];
        e[1] -= v[1];
        e[2] -= v[2];
        return *this;
    }

    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
	e[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
	bool near_zero() const
	{
		auto s = 1e-8;
		return (std::fabs(e[0])<s)&&(std::fabs(e[1])<s)&&(std::fabs(e[2])<s);
	}
	void normalise()
	{
		*this/=length();
	}
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v[0], t*v[1], t*v[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return vec3(t*v[0], t*v[1], t*v[2]);
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}
inline vec3 operator/(const vec3& u, const vec3& v) {
    return vec3(u[0] / v[0], u[1] / v[1], u[2] / v[2]);
}

inline double dot(const vec3& u, const vec3& v) {
    return u[0] * v[0]
         + u[1] * v[1]
         + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(const vec3& v) {
		if(v.length()<=1e-8)printf("near zero\n"); 
    return v / v.length();
}
vec3 random_dir()
{
		vec3 randv =vec3(random_double(),random_double(),random_double()); 
		return unit_vector(randv);
}
vec3 reflect(const vec3& v, const vec3& n)
{
		//normal is assummed to be a unit vector
		return v-2*dot(v,n)*n;
}
vec3 refract(const vec3& i,const vec3& n, double etai_over_etar)
{
		// i and n are normalised and TIR is taken care of
    vec3 r_out_perp =  etai_over_etar * (i -dot(i,n)*n);
    vec3 r_out_parallel = -std::sqrt((1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
inline vec3 rand_unit_disk(vec3 u,vec3 v)
{
		return unit_vector(v*random_double()+u*random_double())*random_double_range(0, 1); 
}
inline vec3 maxVec3(vec3 v1, vec3 v2)
{
		return vec3(fmax(v1[0],v2[0]),fmax(v1[1],v2[1]),fmax(v1[2],v2[2])); 
}
inline vec3 minVec3(vec3 v1, vec3 v2)
{
		return vec3(fmin(v1[0],v2[0]),fmin(v1[1],v2[1]),fmin(v1[2],v2[2])); 
}

#endif
