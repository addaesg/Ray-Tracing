#include "space.h"
#include <limits>

using namespace spc;

double inf = std::numeric_limits<double>::infinity();

Scene::Scene() = default;
Scene::Scene(spc::Spheres spheres, spc::Planes planes, atom::rgb backgroundColor):s(spheres), p(planes), bc(backgroundColor){};

atom::rgb Scene::getIntersectionColor(atom::line ray)
{
    atom::rgb curColor = this->bc;
    double mindist = inf, curdist;
    for(auto sphere: this->s)
    {
        curdist = sphere.intersectsLine(ray);
        if(curdist < mindist)
        {
            mindist = curdist;
            curColor = sphere.color;
        }
    }

    for(auto plane: this->p)
    {
        curdist = plane.intersectsLine(ray);
        if(curdist < mindist)
        {
            mindist = curdist;
            curColor = plane.color;
        }
    }
    return curColor;
};

Screen::Screen() = default;
Screen::Screen(double height, double width, double pixelSize): vRes(height), hRes(width), pixelRes(pixelSize){};

Camera::Camera() = default;
Camera::Camera(
    atom::point3 originGlobal, 
    atom::point3 targetGlobal,
    atom::vector3 up,
    spc::Screen screen,
    double distToScreen
)
{
    this->originGlobal = originGlobal;
    this->targetGlobal = targetGlobal;
    this->distToScreen = distToScreen;
    this->up = up;
    this->screen = screen;
};