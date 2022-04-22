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

    // um array de esferas
    typedef std::vector<shapes::Sphere> Spheres;

    // Um array de planos
    typedef std::vector<shapes::Plane> Planes;

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
        Scene();
        Scene(spc::Spheres spheres, spc::Planes planes, atom::rgb backgroundColor);

        /* 
            scene::getIntersectionColor()
            
            Para cada objeto na cena
            ----Calcula a intersecção do objeto com o raio
            
            Retorna a cor do objeto cuja a intersecção deu a mais próxima
             
            returns%type = rgb;
         */
        atom::rgb getIntersectionColor(atom::line ray); 
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