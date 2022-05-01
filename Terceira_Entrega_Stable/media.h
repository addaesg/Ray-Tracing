#ifndef MEDIA
#define MEDIA

#include "space.h"
#include <vector>
#include <string>

namespace ppm
{
    typedef  std::vector<std::vector<atom::rgb>> img;
    void save2ppm(std::string path, img screen, std::pair<int, int> res);
};

#endif 