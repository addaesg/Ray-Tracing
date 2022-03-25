#ifndef ATOM
#define ATOM

#include <cstdint>
/* 
    Estruturas de dados que serão utilizadas em varias classes.    
*/
namespace atom
{

    // Ponto em um espaço tridimencional
    // Point = {x, y, z}
    // padrão = Ponto na Origem
    struct Point {
        double x = 0.0, y = 0.0, z = 0.0;
        Point();
        Point(double x, double y, double z);
    };

    // Vetor da origem até o ponto {x, y, z}
    // Vetor = {x. y, z}
    // Padrão |vetor| = 0
    struct VectorOrigin {
        double x = 0.0, y = 0.0, z = 0.0;
        VectorOrigin();
        VectorOrigin(double x, double y, double z);
    };
    // Reta da origem até o ponto {x, y, z}
    // Representada por um VectorOrigin
    // reta = {vetor}
    // padrão |reta| = 0
    struct LineOrigin { 
        atom::VectorOrigin v;
        LineOrigin();
        LineOrigin(atom::VectorOrigin v);
      
    };
    // RGB serve para representar as cores
    // cada cor é composta por 3 valores Inteiros entre 0 e 255
    // rgb = {red, blue, green} 
    // cada r||b||g tem tamanho de 1 byte(uint8_t)
    // padrão = Cor Preta
    struct Rgb {
        uint8_t r = 0, g = 0, b = 0;
        Rgb();
        Rgb(uint8_t red, uint8_t green, uint8_t blue);
   };


} // namespace atom

#endif