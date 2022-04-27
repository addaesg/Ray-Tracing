#include "space.h"
#include "shapes.h"
#include "atom.h"
#include "mathutils.h"
#include "media.h"
#include <iostream>

void rayCast(spc::Camera c, spc::Scene s)
{
    for(auto row: c.scr)
        for(spc::Pixel p: row)
            p.second = s.getIntersectionColor(line3::fromPoints(c.originGlobal, p.first));      
    

    ppm::save2ppm("output.txt", c.scr, {c.screen.hRes, c.screen.vRes});
};



int main(int argc, char const *argv[])
{
    int v_res, h_res;
    double s, d;
    atom::point3 e, l;
    atom::vector3 up;
    
    std::cin >> v_res >> h_res;
    std::cin >> s >> d;
    std::cin >> e.x >> e.y >> e.z;
    std::cin >> l.x >> l.y >> l.z;
    std::cin >> up.x >> up.y >> up.z;

    spc::Camera c(e, l, up, {v_res, h_res, s}, d); 
    spc::Spheres ss = {};
    spc::Planes ps = {};
    
    atom::rgb bcc;
    std::cin >> bcc.r >> bcc.g >> bcc.b;
    spc::Scene sc(ss, ps, bcc);
    int k;
    std::cin >> k;
    for(int x = 0; x < k; x++)
    {
        atom::rgb color;
        std::cin >> color.r >> color.g >> color.b;


        char sep;
        std::cin >> sep;
        if(sep == '*')
        {
            double ox, oy, oz, r;
            std::cin >> ox >> oy >>oz >>r;

            sc.s.push_back({{{ox, oy, oz}, r}, color});
        }
        else 
        {
            double ox, oy, oz, nx, ny, nz;
            std::cin >> ox >> oy >>oz >> nx >> ny >> nz;

            sc.p.push_back({{{ox, oy, oz}, {nx, ny, nz}}, color});
        }
    }   
    rayCast(c, sc);
    return 0;
};
