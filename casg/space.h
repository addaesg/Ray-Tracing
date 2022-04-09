#ifndef SPACE
#define SPACE
#include "atom.h"
#include <vector>
#include "shapes.h"


namespace spc
{
    typedef std::vector<shapes::Sphere> Spheres;
    typedef std::vector<shapes::Plane> Planes;

    struct Scene
    {
        spc::Spheres s;
        spc::Planes  p;
        atom::rgb bc;
        Scene();
        Scene(spc::Spheres spheres, spc::Planes planes, atom::rgb backgroundColor);
        atom::rgb getIntersectionColor(atom::line ray); 
    };

    struct Screen
    {
        double vRes, hRes, pixelRes;
        Screen();
        Screen(double height, double width, double pixelSize);
    };
    
    
    class Camera
    {
    public:
        atom::point3 originGlobal, targetGlobal;
        atom::vector3 up;
        spc::Screen screen;
        double distToScreen;
        double translationMatrix[3][3];

        Camera(/* args */);
        ~Camera();
    };
    
} // namespace spc



#endif 