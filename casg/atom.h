#ifndef ATOM
#define ATOM

#include <cstdint>
/* 
  Estruturas de dados que serão utilizadas em varias classes.    
*/
namespace atom
{

    // Ponto em um espaço tridimencional
    // point3 = {x, y, z}
    // padrão = Ponto na Origem
    struct point3 {
        double x = 0.0, y = 0.0, z = 0.0;
        point3();
        point3(double x, double y, double z);
    };

    // Vetor da origem até o ponto {x, y, z}
    // Vetor = {x. y, z}
    // Padrão |vetor| = 0
    struct vector3 {
        double x = 0.0, y = 0.0, z = 0.0;
        vector3();
        vector3(double x, double y, double z);
    };
    
    // rgb serve para representar as cores
    // cada cor é composta por 3 valores Inteiros entre 0 e 255
    // rgb = {red, blue, green} 
    // cada r||b||g tem tamanho de 1 byte(uint8_t)
    // padrão = Cor Preta
    struct rgb {
        uint8_t r = 0, g = 0, b = 0;
        rgb();
        rgb(uint8_t red, uint8_t green, uint8_t blue);
   };
    
    // Reta da origem até o ponto {x, y, z}
    // Representada por um vector3
    // reta = { Ponto ,vetorDiretor}
    // padrão |reta| = 0
    struct line{ 
        atom::point3 p;
        atom::vector3 v;
        line();
        line(atom::point3 point, atom::vector3 vector);
    };

} // namespace atom

#endif