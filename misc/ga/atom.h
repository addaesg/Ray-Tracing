#ifndef ATOM
#define ATOM

#include <tuple>
#include <vector>

namespace atom
{

    // Point = {x, y, z}
    // {0,0,0} padrão
    struct Point {
        double x = 0.0, y = 0.0, z = 0.0;
        std::tuple<double, double, double> values = {x, y, z};
        Point();
        Point(double x, double y, double z);
    };

    // mesma coisa do ponto
    // so muda o conceito
    struct VectorOrigin {
        double x = 0.0, y = 0.0, z = 0.0;
        std::tuple<double, double, double> values = {x, y, z};
        VectorOrigin();
        VectorOrigin(double x, double y, double z);
    };

    // line = {Point1, Point2}
    // {{0,0,0}, {0,0,0}} padrão 
    struct LineOrigin { 
        atom::VectorOrigin v;
        LineOrigin();
        LineOrigin(atom::VectorOrigin v);
      
    };
    
    // rgb = {red, blue, green} cor preta padrão
    // cada r||b||g tem tamanho de 1 byte(uint8_t)
    struct Rgb {
        uint8_t r = 0, g = 0, b = 0;
        std::vector<uint8_t> values = {r, g, b};
        Rgb();
        Rgb(uint8_t red, uint8_t green, uint8_t blue);
   };


} // namespace atom

#endif