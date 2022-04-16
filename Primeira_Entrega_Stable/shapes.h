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

        Sphere();
        Sphere(Sphere::equation e, atom::rgb color);
        
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
        Plane();
        Plane(Plane::equation e, atom::rgb color);
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