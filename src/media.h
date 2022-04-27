#ifndef MEDIA
#define MEDIA

#include "space.h"
#include <vector>
#include <string>

namespace ppm
{
    typedef  std::vector<std::vector<atom::rgb>> img;
    void save2ppm(
        const std::string& path,
        const img& screen,
        const std::pair<int, int>& res);
};

#endif 