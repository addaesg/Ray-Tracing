#ifndef SPACE
#define SPACE
#include "atom.h"
#include "shapes.h"
#include <vector>

/* 
    spc

    O namespace "space" é usado para definir objetos de alto nível que estão no espaço 
    - 1. scene
    - 2. screen
    - 3. Camera
 */
namespace spc
{
    struct lightPoint
    {
        atom::point3 pos;
        atom::rgb color;
        atom::vector3 fcolor;
        lightPoint();
        lightPoint(atom::point3 position, atom::rgb color);
    };

    // um array de esferas
    typedef std::vector<shapes::Sphere> Spheres;

    // Um array de planos
    typedef std::vector<shapes::Plane> Planes;

    // Um array de lightPoints
    typedef std::vector<spc::lightPoint> LightPoints;  
    

    /* 
        Scene

        Recieves: 
        - s : array of all spheres in the scene
        - p : array of all planes in the scene
        - bc: atom::rgb the color of the background

        Methods:
        - getIntersectionColor(): cor retornada pelo objeto da cena com a intersecção mais proxima a origem do raio

        scene = {spc::Spheres, spc::Planes, atom::rgb};
     */
    struct Scene
    {
        // array of spheres in the scene
        spc::Spheres s;
        // array of planes in the scene
        spc::Planes  p;
        // scene default background color
        atom::rgb bc;

        // scene ambient light
        atom::rgb al;
        atom::vector3 fal;
        
        // array of light points
        spc::LightPoints lps;

        Scene();
        Scene(spc::Spheres spheres, spc::Planes planes, atom::rgb backgroundColor, atom::rgb ac, spc::LightPoints lp);

        bool doesInstersect(atom::line ray, atom::point3 final);

        /* 
            scene::getPhongThingsFIO()

            aka.: Get Phong Wrapper From First intersected Object from ray.
            
            Para cada objeto na cena
                ----Calcula a intersecção do objeto com o raio

            Retorna o PhongWrapper do objeto cuja a intersecção deu a mais próxima
        */
        shapes::phongWrapper getPhongThingsFIO(atom::line ray);

        /* 
            scene::getIntersectionColor()
            
            1. Acha o objeto com intersecção mais próxima
            2. Faz o calculo de phong
            3. retorna a cor

            returns%type = rgb(0<=double <= 1);
         */
        atom::rgb getIntersectionColor(atom::line ray); 

        /* 
            Algoritmo de phong
            Provavelmente ce ta procurando por isso
         */
    
        atom::rgb phongRM(shapes::phongWrapper phongThings, atom::line ray);
    };


    /* 
        Screen

        Recieves: 
        - vRes : Quantidade de linhas
        - hRes : Quantidade de colunas
        - pixelRes: Tamanho da aresta do pixel

        screen = {int, int, double};
     */
    struct Screen
    {
        int vRes, hRes;
        double pixelRes;
        Screen();
        Screen(int height, int width, double pixelSize);
    };
    
    /* 
       Camera

        Boa sorte
        soninho
     */    
    class Camera
    {
    public:
        atom::point3 originGlobal, targetGlobal;
        atom::vector3 up;
        spc::Screen screen;
        double distToScreen;
        atom::vector3 u, v, w;
        std::vector<std::vector<double>> baseChangeMatrix;
        
        std::vector<std::vector<atom::point3>> scr;

        Camera();
        Camera(
            atom::point3 originGlobal, 
            atom::point3 targetGlobal,
            atom::vector3 up,
            spc::Screen screen,
            double distToScreen
        );
        ~Camera(){};
        void calculateUVW();
        atom::point3 screenGlobalPoint(double i, double j);
        void genScreenVector();
        
    };
    
} // namespace spc
#endif 