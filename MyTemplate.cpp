//
// Created by bayk on 21.05.2021.
//

#include "comparator.h"
#include <functional>
#include "Map.h"
#include "Map.cpp"

template class Map<int, int>;
template class Map<long, long>;
template class Map<double, double>;
template class Map<int, int, comparator>;
template class Map<int, int, std::less<int>>;
template class Map<double, double, std::less<double>>;
template class Map<int, double, std::less<int>>;
