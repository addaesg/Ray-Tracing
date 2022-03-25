#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <tuple>
const int w = 1920, h = 1080; 
const int fade = 0;

typedef std::vector<int> rgb;


class france
{
private:
    typedef std::vector<std::vector<rgb>> img;
    rgb blue = {0, 35, 149}, white = {255, 255, 255}, red = {237, 41, 57};
    /* data */
public:
    france(){}
    ~france(){};
    france::img genflag(std::pair<int, int>, int fade);
};

france::img france::genflag(std::pair<int, int> d, int fade)
{
    int w = d.first, h = d.second;
    france::img vetor;
    int changeColor = std::floor(w/3);
        // gen vector
    std::vector<rgb> temp = {};
    for(int t = 0; t < h; t++)
    {
        for(int u = 0; u < w; u++){
            if( u < changeColor)
                temp.push_back(blue);
            else if(u < changeColor * 2)
                temp.push_back(white);
            else if(u < changeColor * 3)
                temp.push_back(red);
            else
                temp.push_back({0,0,0});
        }
        vetor.push_back(temp);
        temp.clear();
    }    

    //smooth transaction between colors
    for(int t = 0; t < h; t++)
    {
        for(int u = 0; u < w-1; u++){
            if(vetor[t][u] != vetor[t][u+1])
            {
                rgb cor1 = vetor[t][u+1], cor2 = vetor[t][u];
                for(int x = u-fade; x < u + fade; x++)
                {
                    double r = (double)((x-u)+fade)/(fade*2);
                    vetor[t][x] = {(int)((1.0-r)*cor2[0] + r*cor1[0]),
                                   (int)((1.0-r)*cor2[1] + r*cor1[1]),
                                   (int)((1.0-r)*cor2[2] + r*cor1[2])};
                    
                }
                u += fade;
            }
        }
    }
    return vetor;
}


typedef std::vector<std::vector<rgb>> screen;
void save2PPM6(std::string path, std::pair<int, int> dimensions, screen pixels)
{ 
    
    std::ofstream file(path, std::ios_base::binary); 
    
    if(!file)
        return;
    
    std::stringstream content;
    content << "P6\n" 
            << dimensions.first << ' ' <<  dimensions.second << '\n' 
            << "255\n"
            << "#\n#mb casg\n#\n";

    for(auto j: pixels)
        for(auto i: j)
            content << (char) (i[0]%256) 
                    << (char) (i[1]%256) 
                    << (char) (i[2]%256);

    file << content.rdbuf();
    file.close();
}

int main(int argc, char const *argv[])
{
    france f;
    save2PPM6("morri.ppm", {w, h}, f.genflag({w,h}, fade));
    return 0;
}
