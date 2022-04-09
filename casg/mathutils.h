#ifndef MATHUTILS 
#define MATHUTILS
#include "atom.h"

/* 
    MathUtils
    Header utilizado para funções/operações comumente utilizadas sobre objetos do atom.h" no projeto

*/

/* 
    vec3

    namespace para operações que envolvem o atom::vector3.
 */
namespace vec3
{

    /* 
        vec3::sum()

        Soma de dois vetores.
        Retorna um Vetor3;
    */
    atom::vector3 sum(const atom::vector3 a, const atom::vector3 b);

    /* 
        vec3::mult()
        
        Multiplicação de um vetor por uma constante
        retorna um vetor3;
    */
    atom::vector3 mult(const atom::vector3 a,const double k);

    /* 
        vec3::cross()

        Cross product de dois vetores.
        Retorna vector3;
    */
    atom::vector3 cross(const atom::vector3 a, const atom::vector3 b);
    
    /* 
        vec3::fromPoints()

        Vetor determinado por 2 pontos.
        Retorna vector3;
    */
    atom::vector3 fromPoints(const atom::point3 from, const atom::point3 to);

    /* 
        vec3::normalized()

        Versão normalizada de um vetor.
        Retorna um vector3;
    */
    atom::vector3 normalized(const atom::vector3 a);

    /* 
        vec3::normalizeThis()

        !!! Atenção !!!
        !!! Altera os valores do vetor inserido !!!!

        Versão normalizada de um vetor.
        Não retorna;
    */
    void normalizeThis(atom::vector3& a);

    /* 
        vec3::dot()
        
        Valor do dorProduct entre dois vetores.
        Retorna um double;
    */
    double dot(const atom::vector3 a, const atom::vector3 b);

    /* 
        vec3::lenPow2()

        magnitude^2 de um vetor.
        retorna um double;
    */   
    double lenPow2(const atom::vector3 a);
}

/* 
    line3

    namespace para operações que envolvem o atom::line
*/
namespace line3{
    /* 
        line3::fromPoints()

        Gera uma reta dado 2 pontos.
        
        O primeiro ponto do parametro é considerado PontoOrigem da reta
        O vetor diretor da reta já é calculado e normalizado automaticamente.

        Retorna line;
    */  
    atom::line fromPoints(const atom::point3 from, const atom::point3 to);
}

#endif 