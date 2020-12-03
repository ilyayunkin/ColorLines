#ifndef CONTAINER_CONVENIENCE_H
#define CONTAINER_CONVENIENCE_H

#include <algorithm>

namespace Container {
template <typename C, typename T>
bool contains(const C &c, const T &t)
{
    return std::find(c.begin(), c.end(), t) != c.end();
}
}

#endif // CONTAINER_CONVENIENCE_H
