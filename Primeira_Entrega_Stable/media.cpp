#include "media.h"
#include <sstream>
#include <fstream>
#include "space.h"


void ppm::save2ppm(std::string path, ppm::img screen, std::pair<int, int> res)
{
    int w = res.first, h = res.second;
    std::ofstream file(path, std::ios_base::binary);
    if(!file)
        return;
    
    std::stringstream content;
    content << "P6\n" 
            << "#\n#made by casg\n#\n"
            << res.first<< ' ' <<res.second<< '\n' 
            << "255\n";
    for(auto row: screen)
        for(auto pixel: row)
            content << (char) (pixel.r%256)
                    << (char) (pixel.g%256) 
                    << (char) (pixel.b%256);
    
    file << content.rdbuf();
    file.close();
}