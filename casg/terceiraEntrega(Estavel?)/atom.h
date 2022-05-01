#ifndef ATOM
#define ATOM

#include <cstdint>
/* 
   Atom
   
   Estruturas de dados Atômicas do Projeto.
   Elas são utilizadas por varias classes/funções.
*/
namespace atom
{

    // Ponto 
    // É um ponto em um espaço tridimencional
    // 
    // point3 = {x, y, z}
    // padrão = {0,0,0}
    struct point3 {
        double x = 0.0, y = 0.0, z = 0.0;
        point3();
        point3(double x, double y, double z);
    };

    // Vetor da origem até o ponto {x, y, z}
    // Padrão |vetor| = 0
    //
    // Vetor = {x. y, z}
    // ou
    // Use vec3::fromPoints(A, B) para criar o vetor usando 2 pontos A e B com sentido A->B
    // 
    // Provavelmente você quer normalizar esse vetor: Use vec3::normalizeThis() ou vec3::normalized();
    struct vector3 {
        double x = 0.0, y = 0.0, z = 0.0;
        vector3();
        vector3(double x, double y, double z);
    };
    
    // RGB
    // Estrutura para representar um cor.
    // rgb = {red, blue, green} 
    // padrão = Cor Preta
    //
    // cada cor é composta por 3 valores Inteiros entre 0 e 255
    // cada r||b||g tem tamanho de 1 byte(int)
    struct rgb {
        // Red 
        int r = 0;
        // Green
        int g = 0; 
        // blue
        int b = 0;
        rgb();
        rgb(int red, int green, int blue);
   };
    
    // RETA
    // Representada por um ponto de Origem e o vetor diretor.
    // reta = { Ponto3 , Vector3}
    //
    // Use line3::fromPoints() para criar uma reta a partir de 2 pontos. Assim o vetorDiretor fica normalizado.
    // ou
    // Use vec3::normalizeThis() para normalizar o vetor diretor antes de criar a reta.
    struct line{ 
        // Ponto de Origem da Reta
        atom::point3 p;
        // Vetor diretor da reta.
        // Normalize essa merda
        atom::vector3 v;
        line();
        line(atom::point3 point, atom::vector3 vector);
    };

} // namespace atom

#endif