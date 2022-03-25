#ifndef SHAPES
#define SHAPES

#include "atom.h"



namespace shapes
{
    // Classe Solid: Classe pai para Esfera e Plano :D
    class Solid
    {
    public:
        // cor do sólido
        atom::Rgb color;
        Solid();
        ~Solid();

    }; 

    // Classe Sphere(Equation, color): Basta ler o nome
    // Atributos:
    //   Equation = Sphere::Equation
    //   Color = atom::Rgb
    class Sphere: public Solid
    {
    public:
        /*
          Representar o Raio de uma Esfera
          Struct Sphere::Radius = {double radius} 
         */
        struct Radius{
            double r = 0.0; 
            Radius(double radius); 
            Radius();
        };
        /*
            Representar os elementos da equação de uma Esfera
            Struct Sphere::Equation = {atom::Point center, Sphere::Radius r}
        */ 
        struct Equation{ 
            atom::Point center;  
            Sphere::Radius radius;
            Equation(atom::Point, Sphere::Radius); 
            Equation();
        };
        // equação da esfera
        Sphere::Equation equation;
        Sphere();
        Sphere(Sphere::Equation, atom::Rgb);
    };


    /* 
    Classe Plane(Equation, color): Basta ler
    Atributos:
        Equation = Plane::Equation
        Color = atom::Rgb 
    */
    class Plane: public Solid
    {
    public:
        /*
            Representar os elementos da equação de um Plano
            Struct Plane::Equation = {atom::Point PontoDoPlano, atom::VectorOrigin VetorNormal}
        */ 
        struct Equation{ 
            atom::Point point; 
            atom::VectorOrigin normal;
            Equation(atom::Point, atom::VectorOrigin);
            Equation();  
        };
        // equação do plano
        Plane::Equation equation;
        Plane();
        Plane(Plane::Equation, atom::Rgb);

    };

}

#endif 