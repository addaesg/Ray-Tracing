#include "shapes.h"
#include "mathutils.h"
#include <algorithm>
#include <math.h>
#include <limits>

using namespace shapes;

double inf = std::numeric_limits<double>::infinity();
/* 
    Sphere methods
*/
Sphere::equation::equation() = default;
Sphere::equation::equation(atom::point3 c, double r): c(c),r(r){};
Sphere::Sphere() = default;
Sphere::Sphere(Sphere::equation e, atom::rgb color): formula(e), color(color){};

double Sphere::intersectsLine(const atom::line l)
{
    double epsilon = 0.00001;

    atom::vector3 vpc = vec3::fromPoints(this->formula.c, l.p);
    double uoc = vec3::dot(l.v, vpc);
    double delta = uoc*uoc - (vec3::lenPow2(vpc) - this->formula.r * this->formula.r);
    
    if(delta < -epsilon)
        return -1;

    if(std::abs(delta) <= epsilon)
    {
        if(-uoc < -epsilon)
            return -1;
        return -uoc;
    }

    double sqrtDelta = std::sqrt(delta);
    double param1 = -uoc + sqrtDelta;
    double param2 = -uoc - sqrtDelta;
    
    if(param1 < -epsilon)
        param1 = inf;
    if(param2 < -epsilon)
        param2 = inf;

    double minparam = std::min(param1, param2);
    return((minparam < inf)?minparam:-1);
};

/* 
    Plane methods
*/

Plane::equation::equation() = default;
Plane::equation::equation(atom::point3 p, atom::vector3 n): p(p),n(n){};
Plane::Plane() = default;
Plane::Plane(Plane::equation e, atom::rgb color): formula(e), color(color){};

double Plane::intersectsLine(const atom::line l)
{
    double epsilon = 0.00001;
    double dotln = vec3::dot(l.v,this->formula.n);
    double dotpln = vec3::dot(vec3::fromPoints(l.p, this->formula.p), this->formula.n);
    if (std::abs(dotln) <= epsilon)
    {
        if(std::abs(dotpln) <= epsilon)
            return 0;
        else
            return -1;
    } 
    
    double param = dotpln/dotln;
    return ((param > epsilon)? param:-1);
}

