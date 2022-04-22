#include "space.h"
#include "shapes.h"
#include "atom.h"
#include "mathutils.h"
#include "media.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <ratio>
#include <random>
#include <iomanip>


void rayCast(spc::Camera c, spc::Scene s)
{
    // calc raycast time
    auto start = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);
    
    ppm::img image(c.screen.vRes, std::vector<atom::rgb>(c.screen.hRes, {0,0,0}));
    for(int i = 0; i < c.screen.vRes; i++)
        for(int j = 0; j < c.screen.hRes; j++)
            image[i][j] = s.getIntersectionColor(line3::fromPoints(c.originGlobal, c.scr[i][j]));     
    
    auto end = std::chrono::high_resolution_clock::now();
    auto avg = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;
    std::cout << "Run Time:     " << avg << std::setprecision(9) << " ms\n";
    
    ppm::save2ppm("output.ppm", image, {c.screen.hRes, c.screen.vRes});
};

void run()
{
    int v_res, h_res;
    double s, d;
    atom::point3 e, l;
    atom::vector3 up;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);  
    
    std::cin >> v_res >> h_res;
    std::cout << "V res é " << h_res << "H res é " << v_res << "\n";
    
    std::cout << "Camera: \n"; 
    std::cin >> s >> d;
    std::cout << " O tamanho do pixel é " << s << "\n A distancia para tela é " << d << '\n';
    std::cin >> e.x >> e.y >> e.z;
    std::cout << " A camera está em " << e.x << " " << e.y << " " << e.z << '\n';

    std::cin >> l.x >> l.y >> l.z;
    std::cout << " O target está em " << l.x << " " << l.y << " " << l.z << '\n';

    std::cin >> up.x >> up.y >> up.z;
    std::cout << " O up está em " << up.x << " " << up.y << " " << up.z << '\n';

    spc::Camera c(e, l, up, {v_res, h_res, s}, d); 
    spc::Spheres ss = {};
    spc::Planes ps = {};
    

    atom::rgb bcc;
    std::cin >> bcc.r>> bcc.g >> bcc.b;
    std::cout << "O plano de fundo é " << bcc.r << " " << bcc.g << " " << bcc.b << "\n\n";

    spc::Scene sc(ss, ps, bcc);
    int k;
    std::cin >> k;
    std::cout << "Objetos = " << k << "\n\n\n"; 
    for(int x = 0; x < k; x++)
    {
        atom::rgb color;
        std::cin >> color.r >> color.g >> color.b;
        std::cout << "A cor do objeto é " << color.r << " " << color.g << " " << color.b << "\n\n";


        char sep;
        std::cin >> sep;
        std::cout <<"O separador é " << sep << "\n\n";
        if(sep == '*')
        {
            std::cout << "é uma esfera\n";
            double ox, oy, oz, r;
            std::cin >> ox >> oy >>oz >>r;

            sc.s.push_back({{{ox, oy, oz}, r}, color});
            std::cout << " Esfera:\n Centro: " << ox << " " << oy << " " << oz << "\n Raio: " << r <<"\n\n";

        }
        else 
        {
            std::cout << "é um plano\n";
            double ox, oy, oz, nx, ny, nz;
            std::cin >> ox >> oy >>oz >> nx >> ny >> nz;
            

            sc.p.push_back({{{ox, oy, oz}, {nx, ny, nz}}, color});
            std::cout << " Plano:\n Ponto= " << ox << " " << oy << " " << oz << "\n Normal= " << nx << " " << ny << " " << nz <<"\n\n";
        }
    }    
    rayCast(c, sc);
}


int main(int argc, char const *argv[])
{
    run();
    return 0;
};
