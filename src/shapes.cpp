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


double Sphere::intersectsLine(const atom::line& l) const
{
    // baseado no artigo: https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
    double epsilon = 0.00001;

    atom::vector3 vpc = vec3::fromPoints(this->formula.c, l.p);
    double uoc = vec3::dot(l.v, vpc);
    double delta = uoc*uoc - (vec3::lenPow2(vpc) - this->formula.r * this->formula.r);
    
    // n existe intersecção
    if(delta < -epsilon)
        return -1;

    // a reta toca a esfera.
    if(std::abs(delta) <= epsilon)
    {
        // está atras da origem
        if(-uoc < -epsilon)
            return -1;
        // valido
        return -uoc;
    }
    // existem 2 intersecções
    double sqrtDelta = std::sqrt(delta);
    double param1 = -uoc + sqrtDelta;
    double param2 = -uoc - sqrtDelta;
    // primeira está atras da origem
    if(param1 < -epsilon)
        param1 = inf;
    // segunda está atras da origem
    if(param2 < -epsilon)
        param2 = inf;

    // intersecção mais proxima
    double minparam = std::min(param1, param2);
    // retorna -1 se ambas intersecções forem atras do ponto Origem da reta
    return((minparam < inf)?minparam:-1);
};

/* 
    Plane methods
*/

Plane::equation::equation() = default;
Plane::equation::equation(atom::point3 p, atom::vector3 n): p(p),n(n){};
Plane::Plane() = default;
Plane::Plane(Plane::equation e, atom::rgb color): formula(e), color(color){};

double Plane::intersectsLine(const atom::line& l) const
{
    // baseado no artigo: https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
    double epsilon = 0.00001;
    double dotln = vec3::dot(l.v,this->formula.n);
    double dotpln = vec3::dot(vec3::fromPoints(l.p, this->formula.p), this->formula.n);
    
    // a reta não corta o plano
    if (std::abs(dotln) <= epsilon)
    {
        // é coincidente
        if(std::abs(dotpln) <= epsilon)
            return 0;
        // paralela
        return -1;
    } 
    // corta o plano
    double param = dotpln/dotln;
    // -1 se a intersecção for atras do ponto de origem da reta. distancia cc;
    return ((param > epsilon)? param:-1);
}

