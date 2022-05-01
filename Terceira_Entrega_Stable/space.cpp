#include "space.h"
#include <limits>
#include "mathutils.h"
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace spc;

double infito = std::numeric_limits<double>::infinity();


lightPoint::lightPoint() = default;
lightPoint::lightPoint(atom::point3 position, atom::rgb color):pos(position), color(color){
    this->fcolor = {(color.r*1.0)/255, (color.g*1.0)/255, (color.b*1.0)/255};
};


Scene::Scene() = default;
Scene::Scene(
            spc::Spheres spheres, spc::Planes planes, atom::rgb backgroundColor, 
            atom::rgb ambientLight, LightPoints lps):s(spheres), p(planes), bc(backgroundColor), 
            al(ambientLight), lps(lps)
            {
                this->fal = {(al.r*1.0)/255, (al.g*1.0)/255, (al.b*1.0)/255};
                this->fbc = {(bc.r*1.0)/255, (bc.g*1.0)/255, (bc.b*1.0)/255};
            };


shapes::phongWrapper Scene::getPhongThingsFIO(atom::line ray)
{
    double epsilon = 0.00001;

    double mindist = infito, curdist;
    bool isSphere = false;
    int index;
    // acha o index do menor Obj
    for(int x=0; x<this->s.size(); x++)
    {
        curdist = this->s[x].intersectsLine(ray);
        if(curdist >= -epsilon && curdist < mindist)
        {
            mindist = curdist;
            isSphere = true;
            index = x;
        }
    }

    for(int x=0; x<this->p.size();x++)
    {
        curdist = this->p[x].intersectsLine(ray);
        if(curdist >= -epsilon && curdist < mindist)
        {
            mindist = curdist;
            isSphere = false;
            index=x;
        }
    }
    
    if(mindist == infito)
        return {{-1, -1, -1, -1, {-1,-1,-1}}, {0,0,0}, {0,0,0}, {0,0,0}};
    
    return ((isSphere)? this->s[index].getPhongThings(p3::inLine(ray, mindist)) : 
                        this->p[index].getPhongThings(p3::inLine(ray, mindist)));
}

bool Scene::doesInstersect(atom::line ray, atom::point3 final)
{
    double epsilon = 0.00001;
    double curdist;
    // calcular dist ponto e foco de luz
    double maxdist = std::sqrt(vec3::lenPow2(vec3::fromPoints(ray.p, final)));
    // acha o index do menor Obj
    for(auto sphere: this->s)
    {
        curdist = sphere.intersectsLine(ray);
        if(curdist >= epsilon*0.1 && curdist < infito && curdist < maxdist)
            return true;
    }

    for(auto plane: this->p)
    {
        curdist = plane.intersectsLine(ray);
        if(curdist >= epsilon*0.1 && curdist < infito && curdist < maxdist)
            return true;
    }
    return false;
}

atom::vector3 Scene::phongRTXon(shapes::phongWrapper pw, atom::line ray, int hp)
{
    // Só uma variavel de controle de erro
    double epsilon = 0.001;


    /* 
        Phong reflation model 
    */
    
    // vetor que vai do ponto do ponto de itersecção a camera
    atom::vector3 wo = (vec3::mult(ray.v,-1));
    vec3::normalizeThis(wo);
    
    // ambient color
    atom::vector3 c1 = vec3::multCrime(vec3::mult(pw.dc, pw.k.a), this->fal);
    // instanciando cor difusa e cor especular;
    atom::vector3 c2 = {0,0,0}, c3 = {0,0,0};

    // poupando tempo
    atom::vector3 kdc = vec3::mult(pw.dc,pw.k.d);
    // iterando sobre as luzes da cena
    for(int j=0; j<this->lps.size(); j++)
    {   
        // ignora essa luz se ela faz sombra
        // ou seja, existe um objeto entre ela e o ponto de intersecção
        if(doesInstersect(line3::fromPoints(pw.p, this->lps[j].pos), this->lps[j].pos))
            continue;
    
        // se não faz sombra, então:
    
        // Calcula a cor difusa
        auto lj = vec3::normalized(vec3::fromPoints(pw.p,this->lps[j].pos));
        auto nlj = vec3::dot(pw.n, lj);
        c2 = vec3::sum(vec3::multCrime(kdc, vec3::mult(this->lps[j].fcolor, std::max(0.0, nlj))), c2);
        
        // Calcula cor especular
        if(nlj >= -0.5)
        {
            vec3::normalizeThis(lj);
            auto rm = (vec3::sum(vec3::mult(pw.n ,2.0*(vec3::dot(lj, pw.n))),vec3::mult(lj, -1)));
            auto rmdot = std::max(.0, vec3::dot(rm,wo));
            auto rmpow = std::pow(rmdot, pw.k.n);
            auto esp = this->lps[j].fcolor;
            auto fim = vec3::mult(esp, rmpow); 
            c3 = vec3::sum(fim, c3);
        }
    }
    c3 = vec3::mult(c3, pw.k.s);
    atom::vector3 cor = (vec3::sum(c1, vec3::sum(c2,c3)));//vec3::sum(c1, vec3::sum(c2,c3));

    /* 
        Game over, você tem 0 de vida
        ou seja, chegou no limite setado para quantidade recurções 
        então retorna só a cor do modelo de phong do objeto atingido.
    */
    if(hp == 0)
        return cor;

    /* 
        PARTE RECURSIVA DO RAYTRACING
    */
    double ktt = pw.k.rt.t, ktr = pw.k.rt.r;

    // Calculando o raio de reflexão
    atom::vector3 rvec = vec3::sum(ray.v, vec3::mult(pw.n, -2.0*vec3::dot(ray.v, pw.n)));
    atom::line rray = {p3::sum(pw.p, vec3::mult(pw.n, epsilon)), rvec};
    
    auto rphongThings = getPhongThingsFIO(rray);
    atom::vector3 rcolor;
    
    if(rphongThings.k.a == -1)
        rcolor = this->fbc;
    else
        rcolor = phongRTXon(rphongThings, rray, hp - 1);

    
    // Calculando o raio de refração   
    
    // CALCULA T 
    atom::vector3 tcolor = {0,0,0};
    double coteta = vec3::dot(wo, pw.n);
    atom::vector3 tvec;
    double delta, n;
    atom::vector3 pwn;
    
    // Existem duas posibilidade, ou o vetor de refração está incindindo ou saindo o objeto;
    
    n = pw.k.rt.n;
    pwn = pw.n;
    // Se ele estiver sentido dentro->fora
    if(coteta < -epsilon)
    {
        n = 1/pw.k.rt.n; 
        pwn = vec3::mult(pw.n, -1.0); 
        coteta = vec3::dot(wo, pwn);
    }
    // Senão, ele está incindindo 
    else if(coteta <= epsilon)
        coteta = 0;
    
    
    delta = 1 - ((1 - std::pow(coteta, 2))/std::pow(n, 2));
    // Se delta < 0, não existe raio refratado
    // ou seja, reflexão total
    if(delta < -epsilon)
    {
        ktr = 1.0;
        ktt = 0.0;
    }
    // Senão, então existe refração. Calcule ela
    else 
    {
        if(delta < epsilon)
            delta = 0.0;
        auto parte1 = vec3::mult(wo, -1/n);
        auto parte2 = std::sqrt(delta) - coteta/n;
        auto parte3 = vec3::mult(pwn, -parte2);
        tvec = vec3::sum(parte1, parte3);

        atom::line tray = {p3::sum(pw.p, vec3::mult(pwn, -epsilon)), tvec};
        auto tphongThings = getPhongThingsFIO(tray);
            
        if(tphongThings.k.a == -1)
            tcolor = this->fbc;
        else
            tcolor = phongRTXon(tphongThings, tray, hp - 1);
    }
    
    // multiplica cada cor(reflexão/refração) pela respectiva constante(refração/reflexão) do objeto
    rcolor = vec3::mult(rcolor, ktr);
    tcolor = vec3::mult(tcolor, ktt);    

    // soma com a cor do modelo de phong e retorna. 
    auto rtcolor = vec3::sum(rcolor, tcolor);
    cor = vec3::sum(rtcolor, cor);
    
    return cor;
}

atom::rgb Scene::getIntersectionColor(atom::line ray, int hp)
{
    auto phongThings = getPhongThingsFIO(ray);
    
    if(phongThings.k.a == -1)
        return this->bc;

    atom::vector3 cor = vec3::normalCrime(phongRTXon(phongThings, ray, hp));
    return {(int)(cor.x*255)%255, (int)(cor.y*255)%255, (int)(cor.z*255)%255};
};

Screen::Screen() = default;
Screen::Screen(int height, int width, double pixelSize): vRes(height), hRes(width), pixelRes(pixelSize){};

Camera::Camera() = default;
Camera::Camera(
    atom::point3 originGlobal, 
    atom::point3 targetGlobal,
    atom::vector3 up,
    spc::Screen screen,
    double distToScreen
)
{
    this->originGlobal = originGlobal;
    this->targetGlobal = targetGlobal;
    this->distToScreen = distToScreen;
    this->up = up;
    this->screen = screen;
    
    this->calculateUVW();
    this->genScreenVector();
};

void Camera::calculateUVW()
{
    this->w = vec3::normalized(vec3::fromPoints(targetGlobal, originGlobal));
    this->u = vec3::normalized(vec3::cross(this->up, this->w));
    this->v = vec3::cross(this->w, this->u);
};

atom::point3 Camera::screenGlobalPoint(double i, double j)
{
    double x, y;
    x = this->screen.pixelRes*(j - this->screen.hRes/2 + 0.5);
    y = - this->screen.pixelRes*(i - this->screen.vRes/2 + 0.5);

    atom::vector3 nu, nv, nw;

    nu = vec3::mult(this->u, x);
    nv = vec3::mult(this->v, y);
    nw = vec3::mult(this->w, -this->distToScreen);

    return p3::sum(p3::sum(p3::sum(this->originGlobal, nu), nv), nw);
};

void Camera::genScreenVector()
{
    std::vector<atom::point3> row = {};
    for(int i = 0; i < this->screen.vRes; i++)
    {
        row.clear();
        for(int j = 0; j < this->screen.hRes; j++)
            row.push_back(this->screenGlobalPoint(i, j));
        this->scr.push_back(row);
    }
}