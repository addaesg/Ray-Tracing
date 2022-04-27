#ifndef SHAPES  
#define SHAPES

#include "atom.h"
/* 
    Shapes

    Namespace para definir os objetos geometricos
    1. Esfera
    2. Plano
*/
namespace shapes
{   
    /* 
        shape const values for Phong Algorithm
        Ka = coeficiente ambiental
        Kd = Coeficiente de reflexão difusa
        Ks = coeficiente especular
        n  = expoente de phong

        Fiz dessa forma para podermos facilmente modificar o código
        Seria mais fácil fazer por polymorfismo...
    */
    struct phongConst
    {
        //Ka = coeficiente ambiental
        double a;
        //Kd = Coeficiente de reflexão difusa
        double d;
        //Ks = coeficiente especular
        double s;
        //n  = expoente de phong
        double n;
        phongConst();
        phongConst(double ka, double kd, double ks, double n);
    };
    
    /* 
        Wrapper para Calcular Modelo de reflexão de phong
        k = PhongConst.  Ler descrição do shapes::phongConst
        p = Ponto de intersecção RaioCamera->Objeto
        n = Normal do ponto p.
    */
    struct phongWrapper
    {
        // Phong const
        phongConst k;
        //p = Ponto de intersecção RaioCamera->Objeto
        atom::point3 p;
        //  n = Normal do ponto p.
        atom::vector3 n;
        // cor difusa do objeto
        atom::vector3 dc;
        phongWrapper();
        phongWrapper(phongConst k, atom::point3 p, atom::vector3 n, atom::vector3 c);
    };

    /* 
        Class: Sphere
        Recieves: Sphere::equation, atom::rgb
        Methods: intersectsLine() 
        
        Cria uma esfera
        Ela pode ser criada de duas formas, eu acho:
        -----1. Da forma normal que se declara um objeto de uma classe
        -----2. usando {}. Da mesma forma que é usado para as outras estruturas. (n tenho ctz se funciona :p) 
    */
    class Sphere
    {
    public:
        /* 
            Estrutura para Equação da Esfera

            Atributos: 
            - c = Centro da esfera (point3)
            - r = Raio da esfera (double)
            
            {atom::point3, double}
         */
        struct equation
        {
            // centro da esfera
            atom::point3 c;
            // raio da esfera
            double r;
            equation();
            equation(atom::point3 c, double r);
        };
        // objeto que representa a formula da esfera
        // Veja Sphere::Equation
        Sphere::equation formula;
        // nome auto-explicativo...
        atom::rgb color;
        atom::vector3 fcolor;
        shapes::phongConst k;

        Sphere();
        Sphere(Sphere::equation e, atom::rgb color,  shapes::phongConst k);
        
        /*  
            Get phongWrapper from a sphere
        */
        shapes::phongWrapper getPhongThings(atom::point3 p);


        
        /* 
            shapes::sphere.intersectsLine();
            
            Calcula, se existir, o tamanho do segmento de reta entre o ponto de origem da reta L
            e o ponto de intersecção da reta L com a esfera. 

            Retorna -1, caso:
            ------Não exista intersecção 
            ------OU
            ------Intersecção está atrás do ponto de origem de L.

            Retorna o tamanho, cc

            Retorn%type = double
         */
        double intersectsLine(const atom::line l);

        ~Sphere(){};
    };
    
    /* 
        Class: Plane
        Recieves: Planw::equation, atom::rgb
        Methods: intersectsLine() 
        
        Cria um plano
        Ela pode ser criada de duas formas, eu acho:
        -----1. Da forma normal que se declara um objeto de uma classe
        -----2. usando {}. Da mesma forma que é usado para as outras estruturas. (n tenho ctz se funciona :p) 
    */
    class Plane
    {
    public:
        /* 
        Estrutura para Equação do Plano

        Atributos: 
        - p = Ponto pertencente ao plano
        - n = vetor normal ao plano (pfv normaliza essa merda)
        
        {atom::point3, atom::vector3}
        */
        struct equation
        {
            // ponto no plano
            atom::point3 p;
            // vetor normal (ESPERO QUE NORMALIZADO) ao plano
            atom::vector3 n;
            equation();
            equation(atom::point3 p, atom::vector3 n);
        };
        // Objeto para equação do plano
        // veja plane::equation
        Plane::equation formula;
        
        // basta ler
        atom::rgb color;
        atom::vector3 fcolor;
        shapes::phongConst k;

        

        Plane();
        Plane(Plane::equation e, atom::rgb color, shapes::phongConst k);

        /* 
            getPhongWrapper from a Plane
         */
        shapes::phongWrapper getPhongThings(atom::point3 p);
        /* 
            shapes::plane.intersectsLine();
            
            Calcula, se existir, o tamanho do segmento de reta entre o ponto de origem da reta L
            e o ponto de intersecção da reta L com o plano. 

            Retorna -1, caso:
            ------Não exista intersecção 
            ------OU
            ------Intersecção está atrás do ponto de origem de L.

            Retorna o tamanho, cc
            Obs: Se a reta for coincidente, o tamanho é 0;

            Retorn%type = double
         */
        double intersectsLine(const atom::line l);

        ~Plane(){};
    };
};


#endif