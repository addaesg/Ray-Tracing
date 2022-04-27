#include "space.h"
#include <limits>
#include "mathutils.h"

using namespace spc;

double inf = std::numeric_limits<double>::infinity();

Scene::Scene() = default;
Scene::Scene(spc::Spheres spheres, spc::Planes planes, atom::rgb backgroundColor):s(spheres), p(planes), bc(backgroundColor){};

atom::rgb Scene::getIntersectionColor(atom::line ray)
{
    // vo comentar isso n
    // mó cansado
    double epsilon = 0.00001;
    atom::rgb curColor = this->bc;
    double mindist = inf, curdist;
    for(auto sphere: this->s)
    {

        curdist = sphere.intersectsLine(ray);
        if(curdist >= -epsilon && curdist < mindist)
        {
            mindist = curdist;
            curColor = sphere.color;
        }
    }

    for(auto plane: this->p)
    {
        curdist = plane.intersectsLine(ray);
        if(curdist >= -epsilon && curdist < mindist)
        {
            mindist = curdist;
            curColor = plane.color;
        }
    }
    return curColor;
};

Screen::Screen() = default;
Screen::Screen(int height, int width, double pixelSize): vRes(height), hRes(width), pixelRes(pixelSize){};

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
    
    this->calculateUVW();
    this->genScreenVector();
/*     this->orthoNormalBaseGlobal = orthoNormalBaseGlobal;
    this->baseChangeMatrix = baseChangeMatrix; */
};

void Camera::calculateUVW()
{
    this->w = vec3::normalized(vec3::fromPoints(targetGlobal, originGlobal));
    this->u = vec3::normalized(vec3::cross(this->up, this->w));
    this->v = vec3::cross(this->w, this->u);
};

atom::point3 Camera::screenGlobalPoint(int i, int j)
{
    float x, y;
    x = this->screen.pixelRes*(j - this->screen.hRes/2 + 0.5);
    y = - this->screen.pixelRes*(i - this->screen.vRes/2 + 0.5);

    atom::vector3 nu, nv, nw;

    nu = vec3::mult(this->u, x);
    nv = vec3::mult(this->v, y);
    nw = vec3::mult(this->w, -this->distToScreen);

    return p3::sum(p3::sum(p3::sum(this->originGlobal, nu), nv), nw);
};

void Camera::genScreenVector()
{
    for(int i = 0; i < this->screen.vRes; i++)
    {
        std::vector<Pixel> row = {};
        for(int j = 0; j < this->screen.hRes; j++)
        {
            row.push_back({this->screenGlobalPoint(i, j), {0,0,0}});
        };
        this->scr.push_back(row);
    }
}