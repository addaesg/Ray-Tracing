#include "mathutils.h"
#include <math.h>
#include <cstdint>

atom::vector3 vec3::sum(const atom::vector3 a, const atom::vector3 b)
{
    return {a.x+b.x, a.y+b.y, a.z+b.z};
}

atom::vector3 vec3::mult(const atom::vector3 a,const double k)
{
    return {a.x*k, a.y*k, a.z*k};
}

atom::vector3 vec3::cross(const atom::vector3 a, const atom::vector3 b)
{     
    return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}    

atom::vector3 vec3::fromPoints(const atom::point3 from, const atom::point3 to)
{
    return {to.x - from.x, to.y - from.y, to.z - from.z};
};

atom::vector3 vec3::normalized(const atom::vector3 a)
{
    double pw2 = a.x*a.x + a.y*a.y + a.z*a.z;
    return vec3::mult(a, 1/std::sqrt(pw2));
};

void vec3::normalizeThis(atom::vector3& a)
{
    a = vec3::normalized(a);
}


double vec3::dot(const atom::vector3 a, const atom::vector3 b)
{
    return (a.x*b.x + a.y*b.y + a.z*b.z);
};

double vec3::lenPow2(const atom::vector3 a)
{
    return (a.x*a.x + a.y*a.y + a.z*a.z);
};

atom::line line3::fromPoints(const atom::point3 from, const atom::point3 to)
{
    return {from,  vec3::normalized(vec3::fromPoints(from, to))};
};

atom::point3 p3::sum(atom::point3 p, atom::vector3 v)
{
    return {p.x + v.x, p.y + v.y, p.z + v.z};   
<<<<<<< HEAD:casg/mathutils.cpp
}
=======
}
>>>>>>> c664e0b6f550c3c438960c22f81e69df027e049c:casg/PrimeiraEntrega(Estavel)/mathutils.cpp
